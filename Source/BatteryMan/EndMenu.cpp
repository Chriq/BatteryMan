// Fill out your copyright notice in the Description page of Project Settings.


#include "EndMenu.h"

#include "Blueprint/UserWidget.h"

void AEndMenu::BeginPlay() {

	Super::BeginPlay();

	EndMenu_Widget = CreateWidget(GetWorld(), EndMenu_Widget_Class);
	EndMenu_Widget->AddToViewport();

}