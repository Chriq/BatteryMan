// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Item.h"
#include "BatteryMan_GameMode.generated.h"

/**
 * 
 */

UCLASS()
class BATTERYMAN_API ABatteryMan_GameMode : public AGameMode
{
	GENERATED_BODY()

	ABatteryMan_GameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AItem>> PlayerRecharge;

	int NUM_ITEMS = 3;

	int Total_Spawn_Weights = 0;

	UPROPERTY(EditAnywhere)
	float Spawn_X_Min;

	UPROPERTY(EditAnywhere)
	float Spawn_X_Max;

	UPROPERTY(EditAnywhere)
	float Spawn_Y_Min;

	UPROPERTY(EditAnywhere)
	float Spawn_Y_Max;

	UPROPERTY(EditAnywhere)
	float Spawn_Z_Min;

	UPROPERTY(EditAnywhere)
	float Spawn_Z_Max;

	void SpawnPlayerRecharge();

};
