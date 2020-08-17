// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BatteryMan_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYMAN_API ABatteryMan_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ABatteryMan_PlayerController();

	void ToggleMouseCursor(bool ShowMouse);

};
