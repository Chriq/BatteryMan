// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Blueprint/UserWidget.h"


void AMainMenu::BeginPlay() {

	Super::BeginPlay();

	MainMenu_Widget = CreateWidget(GetWorld(), MainMenu_Widget_Class);
	MainMenu_Widget->AddToViewport();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}

}