// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Cell.h"
#include "EngineUtils.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "CellGeneratorAndController.h"
#include "CellChanger.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALEVEL_API UCellChanger : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCellChanger();

	//// Line trace to see what object it is hitting
	UFUNCTION()
	void LineTraceAndChangeState();

	//// Input Component
	UInputComponent* InputComponent = nullptr;
	UFUNCTION(BlueprintCallable)
	void loading_InputComponent();

	UPROPERTY()
	bool InputComponentLoaded = false;

	//// Change state
	UFUNCTION()
	void ChangeState();
	UFUNCTION()
	void ChangeStateBool();
	bool AllowChangeState = true;

	//// Find address of CellGeneratorAndController
	UFUNCTION()
	AActor* FindCellGeneratorAndController();
	AActor* CellGaC = nullptr;

	//// Toggle Tick
	UFUNCTION()
	void ToggleTickGaC();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// private variables
	float DistanceReach = 999999.f;
		
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
