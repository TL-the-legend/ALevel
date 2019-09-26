// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/Engine.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "TimerPulse.generated.h"

// Part of delegate
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSendPulse, TArray<int>, map);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSendPulse);
DECLARE_DELEGATE_OneParam(FSendPulse, FString);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALEVEL_API UTimerPulse : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTimerPulse();
	


	// Part of delegate
	FSendPulse TickPulse;

	// Timer
	void TimerLoop();
	float TimerDelayTime = 1.f;
	FTimerHandle TimerPulseHandle;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
