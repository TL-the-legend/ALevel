// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cell.h"
#include "Engine/World.h"
#include "CellGeneratorAndController.generated.h"

// 2D array using unreal's TArray
USTRUCT()
struct FCellRow
{
	GENERATED_BODY()
	TArray<ACell*> CellAdrs;
};

UCLASS()
class ALEVEL_API ACellGeneratorAndController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACellGeneratorAndController();

	// Cells info
	UPROPERTY(EditAnywhere)
	uint32 height = 0;
	UPROPERTY(EditAnywhere)
	uint32 width = 0;
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Classes")
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACell> ClassToSpawn;


	// 2D array using unreal's TArray
	TArray<FCellRow> CellCollections;


	// Generating cells
	void GenerateCells();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
