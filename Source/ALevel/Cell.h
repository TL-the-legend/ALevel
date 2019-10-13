// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/Class.h"
#include "Components/MeshComponent.h"
#include "GameFramework/Actor.h"
#include "UObject/UObjectGlobals.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Cell.generated.h"

UENUM()
enum class ECellState : uint8
{
	Alive,
	Dead,
};

UCLASS()
class ALEVEL_API ACell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACell();

	//// State Stuff
	UFUNCTION()
	ECellState ReturnState();

	// initiate state
	UPROPERTY()
	ECellState State = ECellState::Alive;

	// load next state
	ECellState NextNewState = ECellState::Dead;

	UFUNCTION()
	void LoadNextState(ECellState NextState);

	// update state
	UFUNCTION()
	void UpdateState();

	// Change Material
	UFUNCTION()
	void ChangeMaterialAlive();

	UFUNCTION()
	void ChangeMaterialDead();

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* AliveMaterial;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* DeadMaterial;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* ChangeMaterial;

	UFUNCTION()
	void SetUpMaterial();

	UPROPERTY(EditAnywhere, Category = "Meshes")
	UStaticMesh* MeshAsset;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
