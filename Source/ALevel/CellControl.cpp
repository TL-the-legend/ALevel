// Fill out your copyright notice in the Description page of Project Settings.


#include "CellControl.h"
#include "TimerPulse.h"

// Sets default values for this component's properties
UCellControl::UCellControl()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Receive from delegate event dispatcher
void UCellControl::Receiver()
{
	AActor* test;
	auto test = Cast<AActor>(test);
	if (!ensure(test)) { return; }
	test->TickPulse.AddDynamic(this, CellDoSomething());
}

void UCellControl::CellDoSomething()
{
	UE_LOG(LogTemp, Warning, TEXT("Cell doing something"));
}

// Called when the game starts
void UCellControl::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCellControl::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

