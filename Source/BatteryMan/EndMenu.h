// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EndMenu.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYMAN_API AEndMenu : public AHUD
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> EndMenu_Widget_Class;

	UUserWidget* EndMenu_Widget;
	
};
