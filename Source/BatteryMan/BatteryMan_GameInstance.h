// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BatteryMan_GameInstance.generated.h"

/**
 * 
 */

class AItem;

UCLASS()
class BATTERYMAN_API UBatteryMan_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	bool bPlayerIsDead = false;

	int32 Levels_To_Open = 1;

	const int32 NUM_LEVELS = 4;

	UFUNCTION(BlueprintCallable)
	void ResetGame();
	
};
