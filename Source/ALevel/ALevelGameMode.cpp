// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ALevelGameMode.h"
#include "ALevelCharacter.h"
#include "UObject/ConstructorHelpers.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FSendSignal, bool, Pulse)

AALevelGameMode::AALevelGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
