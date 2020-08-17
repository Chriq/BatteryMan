// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryMan_GameMode.h"
#include "BatteryManPlayer.h"
#include "BatteryMan_PlayerController.h"
#include "Item.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

ABatteryMan_GameMode::ABatteryMan_GameMode() {

	PrimaryActorTick.bCanEverTick = true;
}

void ABatteryMan_GameMode::BeginPlay() {
	Super::BeginPlay();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &ABatteryMan_GameMode::SpawnPlayerRecharge, FMath::RandRange(2,5), true);
}

void ABatteryMan_GameMode::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ABatteryMan_GameMode::SpawnPlayerRecharge() {
	float RandX = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);
	float RandY = FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max);
	float RandZ = FMath::RandRange(Spawn_Z_Min, Spawn_Z_Max);

	FVector SpawnPosition = FVector(RandX, RandY, RandZ);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	
	/*
	// Iterates through the list of spawnable items and sums the spawn weights
	// TODO: Need to figure out
	for (int i = 0; i < NUM_ITEMS; i++) {
		Item_Spawned = Cast<AItem>(PlayerRecharge[i]);
		if (Item_Spawned) {
			UE_LOG(LogTemp, Warning, TEXT("Casted"));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Not Casted"));
		}
		//Total_Spawn_Weights += Item_Spawned.Spawn_Weight;
	}*/
	
	// Choose random number for spawn selection
	//int Rand = FMath::RandRange(0, Total_Spawn_Weights);
	float Rand = FMath::RandRange(0.0f, 10.0f);

	// Iterates through spawnable items and tries to cast as Item object
	// Weight variable stores the summed weights to compare to the random number
	//if Weight > the random number, store the index in Weight and break from loop
	// TODO: Need to figure out
	/*
	int Weight = 0;
	for (int i = 0; i < NUM_ITEMS; i++) {
		Item_Spawned = PlayerRecharge[Weight];

		UE_LOG(LogTemp, Warning, TEXT("Item Casted"));
		Weight += Item_Spawned.Spawn_Weight;
		if (Weight > Rand) {
			Weight = i;
			break;
		}

	}*/

	// Spawn AItem actor from the array based on index found above
	// TODO: Need to figure out, hard coding probabilities for now
	if (Rand <= 8.0f)
		GetWorld()->SpawnActor<AItem>(PlayerRecharge[0], SpawnPosition, SpawnRotation);
	else if (Rand > 8.0f && Rand <= 9.5f)
		GetWorld()->SpawnActor<AItem>(PlayerRecharge[1], SpawnPosition, SpawnRotation);
	else
		GetWorld()->SpawnActor<AItem>(PlayerRecharge[2], SpawnPosition, SpawnRotation);
}