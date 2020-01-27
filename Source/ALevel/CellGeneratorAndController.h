// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cell.h"
#include "Engine/World.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "UObject/Class.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"
#include "EngineUtils.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Controller.h"
#include "CellChanger.h"
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
	// Blueprint calling test function
	UFUNCTION(BlueprintCallable)
	void BPtestFunction();

	// Sets default values for this actor's properties
	ACellGeneratorAndController();

	//// Cells info
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Dimentions")
	int32 height = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Dimentions")
	int32 width = 0;

	UPROPERTY(EditAnywhere, Category = "Class To Spawn")
	TSubclassOf<ACell> ClassToSpawn;

	UPROPERTY(EditAnywhere, Category = "Meshes")
	UStaticMesh* MeshAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Game State")
	bool GameStarted = false;


	//// 2D array using unreal's TArray
	TArray<FCellRow> CellCollections;

	//// Generate all the cells that will be in the game
	UFUNCTION(BlueprintCallable)
	void GenerateCells(int32 PassedInHeight, int32 PassedInWidth);

	UPROPERTY()
	bool CellGenerated = false;

	UFUNCTION()
	bool ReturnCellGenerated();

	//// Observe and decide if the cell should be alive or dead in the next state
	UFUNCTION()
	void ObserveCells(ACell* ThisCell, uint8 X_Axis, uint8 Y_Axis);

	ECellState TopLeftCell(uint8 X_Axis, uint8 Y_Axis);

	ECellState TopCell(uint8 X_Axis, uint8 Y_Axis);

	ECellState TopRightCell(uint8 X_Axis, uint8 Y_Axis);

	ECellState LeftCell(uint8 X_Axis, uint8 Y_Axis);

	ECellState RightCell(uint8 X_Axis, uint8 Y_Axis);

	ECellState BottomLeftCell(uint8 X_Axis, uint8 Y_Axis);

	ECellState BottomCell(uint8 X_Axis, uint8 Y_Axis);

	ECellState BottomRightCell(uint8 X_Axis, uint8 Y_Axis);

	uint8 CheckTopLeftCell(uint8 LivingNeighbours, uint8 X_Axis, uint8 Y_Axis);

	uint8 CheckTopCell(uint8 LivingNeighbours, uint8 X_Axis, uint8 Y_Axis);

	uint8 CheckTopRightCell(uint8 LivingNeighbours, uint8 X_Axis, uint8 Y_Axis);

	uint8 CheckLeftCell(uint8 LivingNeighbours, uint8 X_Axis, uint8 Y_Axis);

	uint8 CheckRightCell(uint8 LivingNeighbours, uint8 X_Axis, uint8 Y_Axis);

	uint8 CheckBottomLeftCell(uint8 LivingNeighbours, uint8 X_Axis, uint8 Y_Axis);

	uint8 CheckBottomCell(uint8 LivingNeighbours, uint8 X_Axis, uint8 Y_Axis);

	uint8 CheckBottomRightCell(uint8 LivingNeighbours, uint8 X_Axis, uint8 Y_Axis);

	//// Update cells state
	UFUNCTION()
	void UpdateCellState(ACell* myCell);

	//// Timer do something each pulse
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Timer_Variables")
	float TimerDelayTime = 0.f;

	UPROPERTY()
	float timer = 0.f;
	
	//// Things to do each tick
	UFUNCTION()
	void AllCellTick();

	//// Tick flipflop
	UPROPERTY()
	bool AllowTick = false;
	UFUNCTION()
	void ToggleTick();

	//// Return the cell address
	//ACell* ReturnCellArress(AActor* CellAActorAdress);

	//// Input Component
	UInputComponent* InputComponent = nullptr;
	//UFUNCTION()
	//void loading_InputComponent();

	//// Getting own address
	UPROPERTY()
	AActor* OwnAdrs = nullptr;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

