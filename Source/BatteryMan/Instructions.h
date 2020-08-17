// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Instructions.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYMAN_API AInstructions : public AHUD
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> Instructions_Widget_Class;

	UUserWidget* Instructions_Widget;
	
};
