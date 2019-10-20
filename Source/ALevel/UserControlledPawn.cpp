// Fill out your copyright notice in the Description page of Project Settings.


#include "UserControlledPawn.h"

// Sets default values
AUserControlledPawn::AUserControlledPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUserControlledPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUserControlledPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUserControlledPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

