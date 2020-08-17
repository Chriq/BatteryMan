// Fill out your copyright notice in the Description page of Project Settings.


#include "Instructions.h"

#include "Blueprint/UserWidget.h"

void AInstructions::BeginPlay() {

	Super::BeginPlay();

	Instructions_Widget = CreateWidget(GetWorld(), Instructions_Widget_Class);
	Instructions_Widget->AddToViewport();

}