// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TimerPulse.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "CellControl.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALEVEL_API UCellControl : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCellControl();

	// Part of delegate

	virtual void PostInitializeComponents();
	UFUNCTION()
	void Recevier(int test);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Cell Control
	UFUNCTION()
	void CellDoSomething();
	//void CellDoSomething(int input_int);

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
