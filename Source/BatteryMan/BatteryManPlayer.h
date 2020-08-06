// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Blueprint/UserWidget.h"

#include "BatteryManPlayer.generated.h"

class UBatteryMan_GameInstance;
class AItem;

UCLASS()
class BATTERYMAN_API ABatteryManPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABatteryManPlayer();

	// Holds camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* cameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* followCamera;

	void moveForward(float axis);
	void moveRight(float axis);

	bool bDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	float power;

	UPROPERTY(EditAnywhere, Category = "Item")
	float powerThreshold;

	UFUNCTION()
	void onBeginOverlap(class UPrimitiveComponent* HitComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComponent,
			int OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> Player_Power_Widget_Class;
	UUserWidget* Player_Power_Widget;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> Inventory_Widget_Class;
	UUserWidget* Inventory_Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AItem*> Inventory_Space;

	UFUNCTION(BlueprintPure)
	bool Add_Item_To_Inventory(AItem* Item);

	UFUNCTION(BlueprintPure)
	UTexture2D* GetThumbnailAtSlot(int32 Slot);

	UPROPERTY(EditAnywhere)
	float LevelTime;

	UPROPERTY(BlueprintReadOnly)
	float CurrentTime;

	void RestartGame();

	void TimeLevel();	

	bool InventoryToggled = false;
	void toggleInventory();

	UBatteryMan_GameInstance* Instance;

	int32 INVENTORY_SIZE = 15;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
