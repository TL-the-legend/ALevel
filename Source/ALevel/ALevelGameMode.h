// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ALevelGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSend, bool, Pulse);

UCLASS(minimalapi)
class AALevelGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AALevelGameMode();

	UPROPERTY(BlueprintAssignable)
	FSend SendSignal;
};



