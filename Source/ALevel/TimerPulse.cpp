// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerPulse.h"
#include "Runtime/Engine/Public/TimerManager.h"

// Sets default values for this component's properties
UTimerPulse::UTimerPulse()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTimerPulse::TimerLoop()
{
	UE_LOG(LogTemp, Warning, TEXT("pulse bop bop"));
	int test = 12345;
	//TickPulse.Broadcast(test);
	TickPulse.Broadcast();
}

// Called when the game starts
void UTimerPulse::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	// UWorld
	UWorld* World = GetWorld();
	// Setting up the timer
	World->GetWorld()->GetTimerManager().SetTimer(TimerPulseHandle, this, &UTimerPulse::TimerLoop, TimerDelayTime, true, 1.f);
	
}


// Called every frame
void UTimerPulse::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

