// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageArea.h"
#include "BatteryManPlayer.h"

// Sets default values
ADamageArea::ADamageArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADamageArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamageArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
