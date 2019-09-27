// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ALevelGameMode.h"
#include "ALevelCharacter.h"
#include "UObject/ConstructorHelpers.h"

AALevelGameMode::AALevelGameMode()
{
	
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/CharacterBP/DefaultPawn_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
}
