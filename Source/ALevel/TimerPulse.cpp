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

/*
void UTimerPulse::TimerLoop()
{
	UE_LOG(LogTemp, Warning, TEXT("pulse bop bop"));
	//TArray<int> test = {1,2,3,4,5};
	FString test = TEXT("asdsdasd");
	if (TickPulse.IsBound()) {
		UE_LOG(LogTemp, Warning, TEXT("bounded"));
		//TickPulse.ExecuteIfBound(test);
		TickPulse.Execute(test);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("not bound"));
	}
	
	//TickPulse.Broadcast();
}

*/
// Called when the game starts
void UTimerPulse::BeginPlay()
{
	Super::BeginPlay();

	// ...
	/*
	// UWorld
	UWorld* World = GetWorld();
	// Setting up the timer
	World->GetWorld()->GetTimerManager().SetTimer(TimerPulseHandle, this, &UTimerPulse::TimerLoop, TimerDelayTime, true, 1.f);
	*/
}

/*
// Called every frame
void UTimerPulse::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
*/
// Called every frame
void UTimerPulse::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//In begin play, comment out the line "World->GetWorld()->GetTimerManager().SetTimer(TimerPulseHandle, this, &UTimerPulse::TimerLoop, TimerDelayTime, true, 1.f);"
	//Make TimerDelayTime a UPROPERTY(EditAnywhere)

	//Set up a float in the .h - call it timer. initialise to 0.f;

	timer += DeltaTime;

	if (timer >= TimerDelayTime)
	{
		float timerLeftOvers = timer - TimerDelayTime;
		FString test = TEXT("asdsdasd");
		
		// Dynamic Delegate
		/*
		if (TickPulse.IsBound()) {
			UE_LOG(LogTemp, Warning, TEXT("bounded"));
			TickPulse.ExecuteIfBound(test);
			//TickPulse.Execute(test);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("not bound"));
		}
		*/
		/*
		if (TickPulse.ExecuteIfBound(test)) 
		{
			UE_LOG(LogTemp, Warning, TEXT("bounded"));
		}
		else 
		{
			UE_LOG(LogTemp, Warning, TEXT("not bounded"));
		}
		*/

		// MultiCast Dynamic
		TickPulse.Broadcast(test);
		//TickPulse.ExecuteIfBound(test);
		timer = timerLeftOvers;
	}
}
