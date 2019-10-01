// Fill out your copyright notice in the Description page of Project Settings.


#include "CellGeneratorAndController.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

// Sets default values
ACellGeneratorAndController::ACellGeneratorAndController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACellGeneratorAndController::GenerateCells()
{
	/*
	UWorld* World = GetWorld();
	uint32 foo = 0;
	for (uint32 i = 0; i < 5; i++) 
	{
		foo++;
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		FVector Location = { 100.f, 100.f, 0.f };
		FRotator Rotation = FRotator();
		ACell* myCellName = World->SpawnActor<ACell>(ClassToSpawn, Location, Rotation, SpawnParams);
		UE_LOG(LogTemp, Warning, TEXT("foo = %u; i = %u"), foo, i);
	}
	*/
	/**/
	//// Spawn actors and put their address into a 2D array
	UWorld* World = GetWorld();
	for (uint8 i = 0; i < height; i++) {
		FCellRow thisRow;
		CellCollections.Add(thisRow);
		UE_LOG(LogTemp, Warning, TEXT("heightloop = %u"), i);
		for (uint8 j = 0; j < width; j++) {	
			ACell* myNewCell = nullptr;
			if (World) {
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				FVector Location = { (float)i * 110.f, (float)j * 110.f, 0.f };
				FRotator Rotation = FRotator();
				myNewCell = World->SpawnActor<ACell>(ClassToSpawn, Location, Rotation, SpawnParams);
				UE_LOG(LogTemp, Warning, TEXT("Spawned"));
				CellCollections[i].CellAdrs.Add(myNewCell);
			}
			
			UE_LOG(LogTemp, Warning, TEXT("widthloop = %u"), j);
		}
	}
	//*/
	
}

void ACellGeneratorAndController::ObserveCells()
{

}

// Called when the game starts or when spawned
void ACellGeneratorAndController::BeginPlay()
{
	Super::BeginPlay();

	GenerateCells();
	//UEnum State = CellCollections[0].CellAdrs[0]->ReturnState();
	ECellState State = CellCollections[0].CellAdrs[0]->ReturnState();
	
	if (State == ECellState::Alive) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Alive"));
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Dead"));
	}
}

// Called every frame
void ACellGeneratorAndController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

