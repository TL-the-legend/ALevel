// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cell.h"
#include "Engine/World.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "UObject/Class.h"
#include "UObject/ConstructorHelpers.h"
#include "CellGeneratorAndController.generated.h"

//// 2D array using unreal's TArray
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

	//// Cells info
	UPROPERTY(EditAnywhere)
	uint8 height = 0;
	UPROPERTY(EditAnywhere)
	uint8 width = 0;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACell> ClassToSpawn;
	UPROPERTY(EditAnywhere)
	UStaticMesh* MeshAsset;

	//// 2D array using unreal's TArray
	TArray<FCellRow> CellCollections;

	//// Generate all the cells that will be in the game
	void GenerateCells();

	//// Observe and decide if the cell should be alive or dead in the next state
	void ObserveCells(ACell* ThisCell, uint8 X_Axis, uint8 Y_Axis);
	ECellState TopLeftCell(uint8 X_Axis, uint8 Y_Axis);
	ECellState TopCell(uint8 X_Axis, uint8 Y_Axis);
	ECellState TopRightCell(uint8 X_Axis, uint8 Y_Axis);
	ECellState LeftCell(uint8 X_Axis, uint8 Y_Axis);
	ECellState RightCell(uint8 X_Axis, uint8 Y_Axis);
	ECellState BottomLeftCell(uint8 X_Axis, uint8 Y_Axis);
	ECellState BottomCell(uint8 X_Axis, uint8 Y_Axis);
	ECellState BottomRightCell(uint8 X_Axis, uint8 Y_Axis);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
