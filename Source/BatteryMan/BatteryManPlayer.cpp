// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryManPlayer.h"
#include "BatteryMan_GameInstance.h"
#include "BatteryMan_PlayerController.h"
#include "DamageArea.h"
#include "Item.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"		//for restarting game


// Sets default values
ABatteryManPlayer::ABatteryManPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size of capsule containing character mesh
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// Prevents character itself from rotating so rotation controls can go to camera
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;

	// Orients character toward direction of movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Creates compnent visible in editor
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	// attaches camera to capsule (root component)
	cameraBoom->SetupAttachment(RootComponent);
	// sets camera distance from player
	cameraBoom->TargetArmLength = 300.0f;
	//rotate arm based on controller
	cameraBoom->bUsePawnControlRotation = true;

	//creates camera
	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// Attaches camera to boom
	followCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);
	// Prevents camera from rotating relative to boom
	followCamera->bUsePawnControlRotation = false;

	Instance = Cast<UBatteryMan_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	bDead = false;
	bIsRunning = false;
	power = 100.0f;

}

// Called when the game starts or when spawned
void ABatteryManPlayer::BeginPlay()
{
	Super::BeginPlay();

	ABatteryMan_PlayerController* PC = Cast<ABatteryMan_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	if (PC) {
		PC->ToggleMouseCursor(false);
	}


	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABatteryManPlayer::onBeginOverlap);
	
	Player_Power_Widget = CreateWidget(GetWorld(), Player_Power_Widget_Class);
	Player_Power_Widget->AddToViewport();

	FTimerHandle LevelTimeHandle;
	GetWorldTimerManager().SetTimer(
		LevelTimeHandle, this, &ABatteryManPlayer::TimeLevel, 1.0f, true);

	CurrentTime = LevelTime;

}

// Called every frame
void ABatteryManPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	
	*/
	if (power <= 0) {
		if (!bDead) {
			bDead = true;
			GetMesh()->SetSimulatePhysics(true);

			// FTimerHandle param, this, function to call, after 3 seconds, do not repeatedly call every 3 secs
			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(
				UnusedHandle, this, &ABatteryManPlayer::RestartGame, 3.0f, false);
		}
	}

	if (bIsRunning) {
		power -= DeltaTime * 3 * powerThreshold;
	} else {
		power -= DeltaTime * powerThreshold;
	}
}

// Called to bind functionality to input
void ABatteryManPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABatteryManPlayer::moveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABatteryManPlayer::moveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ABatteryManPlayer::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ABatteryManPlayer::StopRunning);

}

void ABatteryManPlayer::moveForward(float axis)
{
	if (!bDead) {

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, axis);

	}
}

void ABatteryManPlayer::moveRight(float axis)
{

	if (!bDead) {

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, axis);

	}

}


void ABatteryManPlayer::onBeginOverlap(UPrimitiveComponent* HitComp, 
	AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, 
	bool bFromSweep, const FHitResult & SweepResult)
{
	if(OtherActor->ActorHasTag(TEXT("Item"))){
		AItem* HitActor = Cast<AItem>(OtherActor);
		power += HitActor->Power;

		if (power > 100.0f) {
			power = 100.0f;
		}

		OtherActor->Destroy();
	}
	
	else if (OtherActor->ActorHasTag(TEXT("Damage"))) {
		power = 0.0f;
		bDead = true;
		GetMesh()->SetSimulatePhysics(true);

		FTimerHandle OnDeathHandle;
		GetWorldTimerManager().SetTimer(
			OnDeathHandle, this, &ABatteryManPlayer::RestartGame, 3.0f, false);
	}

}

void ABatteryManPlayer::Run()
{
	GetCharacterMovement()->MaxWalkSpeed = 600;
	bIsRunning = true;
}

void ABatteryManPlayer::StopRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 375;
	bIsRunning = false;
}

void ABatteryManPlayer::RestartGame()
{
	Instance->bPlayerIsDead = true;
	UGameplayStatics::OpenLevel(this, FName(TEXT("EndMap")), false);

	ABatteryMan_PlayerController* PC = Cast<ABatteryMan_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC) {
		PC->ToggleMouseCursor(true);
	}
}

void ABatteryManPlayer::TimeLevel()
{
	CurrentTime--;
	if (CurrentTime == 0) {

		//SaveInventory();
		Instance->Levels_To_Open++;

		if (Instance->Levels_To_Open <= Instance->NUM_LEVELS) {

			FName Level_Name = FName(TEXT("Level_" + FString::FromInt(Instance->Levels_To_Open)));
			UGameplayStatics::OpenLevel(this, Level_Name, false);

		}
		else{

			UGameplayStatics::OpenLevel(this, FName(TEXT("EndMap")), false);

			ABatteryMan_PlayerController* PC = Cast<ABatteryMan_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			if (PC) {
				PC->ToggleMouseCursor(true);
			}

		}
	}
}

/* Maybe make a pause screen
void ABatteryManPlayer::toggleInventory()
{
	if (InventoryToggled) {
		if (Inventory_Widget) {
			Inventory_Widget->RemoveFromParent();
			InventoryToggled = false;
		}
	}
	else {
		Inventory_Widget = CreateWidget(GetWorld(), Inventory_Widget_Class);
		Inventory_Widget->AddToViewport();
		InventoryToggled = true;
	}
}
*/