// Fill out your copyright notice in the Description page of Project Settings.


#include "ReportLocation.h"

// Sets default values for this component's properties
UReportLocation::UReportLocation()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UReportLocation::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UReportLocation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	FString Location_Vector = GetOwner()->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("I am at %s"), *Location_Vector);
}

