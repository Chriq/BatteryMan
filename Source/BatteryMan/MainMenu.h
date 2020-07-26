// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYMAN_API AMainMenu : public AHUD
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> MainMenu_Widget_Class;

	UUserWidget* MainMenu_Widget;
	
};
