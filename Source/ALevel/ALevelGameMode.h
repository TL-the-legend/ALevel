// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"
#include "ALevelGameMode.generated.h"


// Declare a delegate for synchronizing the cells
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSend, bool, Pulse);

UCLASS(minimalapi)
class AALevelGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AALevelGameMode();

	// part of delegate for synchronizing 
	UPROPERTY(BlueprintAssignable)
	FSend SendSignal;

	// timer
	void TimerLoop();

	UFUNCTION()
	void SendPulse();

	bool IsTimerOn = true;

	float TimerDelay = 1.f;

	FTimerHandle TimerHandle;

};



