// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerPulse.h"
#include "IndividualCellControl.generated.h"

/**
 * 
 */
UCLASS()
class ALEVEL_API UIndividualCellControl : public UTimerPulse
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
