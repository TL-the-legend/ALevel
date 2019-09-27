// Fill out your copyright notice in the Description page of Project Settings.


#include "CellGeneratorAndController.h"

// Sets default values
ACellGeneratorAndController::ACellGeneratorAndController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACellGeneratorAndController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACellGeneratorAndController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

