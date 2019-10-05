// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "GameFramework/Actor.h"
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
	ECellState State = ECellState::Dead;
	// load next state
	ECellState NextNewState = ECellState::Dead;
	UFUNCTION()
	void LoadNextState(ECellState NextState);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
