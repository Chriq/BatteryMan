// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryMan_GameMode.h"
#include "BatteryManPlayer.h"
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
	float RandX = FMath::RandRange(Spawn_X_Min, Spawn_Y_Max);
	float RandY = FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max);

	FVector SpawnPosition = FVector(RandX, RandY, Spawn_Z);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	
	// Iterates through the list of spawnable items and sums the spawn weights
	for (int i = 0; i < NUM_ITEMS; i++) {
		Item_Spawned = Cast<AItem>(PlayerRecharge[i]);
		if (Item_Spawned) {
			Total_Spawn_Weights += Item_Spawned->Spawn_Weight;
		}
	}

	// Choose random number for spawn selection
	int Rand = FMath::RandRange(0, Total_Spawn_Weights);

	// Iterates through spawnable items and tries to cast as Item object
	// Weight variable stores the summed weights to compare to the random number
	//if Weight > the random number, store the index in Weight and break from loop
	int Weight = 0;
	for (int i = 0; i < NUM_ITEMS; i++) {
		Item_Spawned = Cast<AItem>(PlayerRecharge[Weight]);
		if (Item_Spawned) {
			Weight += Item_Spawned->Spawn_Weight;
			if (Weight > Rand) {
				Weight = i;
				break;
			}
		}
	}
	
	FActorSpawnParameters Params;
	Params.Owner = this;

	// Spawn AItem actor from the array based on index found above
	GetWorld()->SpawnActor<AItem>(PlayerRecharge[Weight], SpawnPosition, SpawnRotation, Params);
}