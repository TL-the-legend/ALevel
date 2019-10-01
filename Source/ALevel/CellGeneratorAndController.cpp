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
	UE_LOG(LogTemp, Warning, TEXT("Function called"));
	UWorld* World = GetWorld();
	for (uint32 i = 0; i < height; i++) {
		FCellRow thisRow;
		CellCollections.Add(thisRow);
		UE_LOG(LogTemp, Warning, TEXT("Step1"));
		UE_LOG(LogTemp, Warning, TEXT("heightloop = %u"), i);
		for (uint32 j = 0; j < width; j++) {
			
			ACell* myNewCell = nullptr;
			UE_LOG(LogTemp, Warning, TEXT("Step2"));
			if (World) {
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				FVector Location = { (float)i * 100.f, (float)j * 100.f, 0.f };
				FRotator Rotation = FRotator();
				myNewCell = World->SpawnActor<ACell>(ClassToSpawn, Location, Rotation, SpawnParams);
				//myNewCell = World->SpawnActor<ACell>(GetClass(), Location, Rotation, SpawnParams);
				UE_LOG(LogTemp, Warning, TEXT("Spawned"));
				CellCollections[i].CellAdrs.Add(myNewCell);
			}
			
			UE_LOG(LogTemp, Warning, TEXT("widthloop = %u"), j);
		}
	}
	//*/
	
}

// Called when the game starts or when spawned
void ACellGeneratorAndController::BeginPlay()
{
	Super::BeginPlay();
	/*
	static ConstructorHelpers::FObjectFinder<UBlueprint> ClassToSpawn(TEXT("Blueprint'/Game/World/Cell_BP.Cell_BP'"));
	if (ClassToSpawn.Object) {
		ClassToSpawn = (UClass*)ClassToSpawn.Object->GeneratedClass;
	}
	*/
	GenerateCells();
}

// Called every frame
void ACellGeneratorAndController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

