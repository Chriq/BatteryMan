// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BatteryMan_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYMAN_API UBatteryMan_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	bool bPlayerIsDead = false;

	int Levels_Complete = 0;

	const int NUM_LEVELS = 3;
	
};
