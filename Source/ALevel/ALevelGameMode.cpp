// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ALevelGameMode.h"
#include "ALevelCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

AALevelGameMode::AALevelGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Begin
	UE_LOG(LogTemp, Warning, TEXT("GAME START"));
	TimerLoop();

}

void AALevelGameMode::TimerLoop()
{
	if(IsTimerOn)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AALevelGameMode::SendPulse, TimerDelay, true, 1.f);
	}
}

void AALevelGameMode::SendPulse()
{
	SendSignal.Broadcast(true);
	SendSignal.Broadcast(false);
	UE_LOG(LogTemp, Warning, TEXT("bruh moment"));
}

