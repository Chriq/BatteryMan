// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryMan_PlayerController.h"

ABatteryMan_PlayerController::ABatteryMan_PlayerController() {

	this->bShowMouseCursor = true;
	this->bEnableClickEvents = true;
	this->bEnableMouseOverEvents = true;

}

void ABatteryMan_PlayerController::ToggleMouseCursor(bool ShowMouse)
{
	this->bShowMouseCursor = ShowMouse;
	this->bEnableClickEvents = ShowMouse;
	this->bEnableMouseOverEvents = ShowMouse;
}
