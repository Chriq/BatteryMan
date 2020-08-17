// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryMan_GameInstance.h"
#include "Item.h"

void UBatteryMan_GameInstance::ResetGame()
{
	Levels_To_Open = 1;
	bPlayerIsDead = false;
}