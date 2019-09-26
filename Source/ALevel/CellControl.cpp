// Fill out your copyright notice in the Description page of Project Settings.


#include "CellControl.h"
#include "TimerPulse.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UCellControl::UCellControl()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
	//Super::PostInitializeComponents();
// Receive from delegate event dispatcher


void UCellControl::Recevier(TArray<int> test)
{
	//AActor Sender = Null;
	//ACharacter* Sender = UGameplayStatics::GetPlayerChracter(GetWorld(), 0);
	//AActor* Sender =
	//Sender->TickPulse.AddDynamic(this, UCellControl::CellDoSomething(test));
}

void UCellControl::FindSender()
{
	// Getting the adress of the sender
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.

		AActor* ActorI = *ActorItr;
		UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *ActorI->GetFName().ToString())
			if (ActorI->GetFName().ToString().Contains(TEXT("Commander"))) 
			{
				Sender = ActorI;
				Attatch_Commander();
				break;
			}
			//ClientMessage(ActorItr->GetActorLocation().ToString());
	}
}

/*
void UCellControl::CellDoSomething(TArray<int> input_int)
{
	UE_LOG(LogTemp, Warning, TEXT("Cell doing something"));
}
*/

void UCellControl::Attatch_Commander()
{
	if (Sender != nullptr) 
	{
		UTimerPulse* localTimerPulse = Sender->FindComponentByClass<UTimerPulse>();
		//UTimerPulse* localTimerPulse = Sender->FindComponentByClass(TSubclassOf<UTimerPulse>)(ComponentClass)
			if (localTimerPulse != nullptr) 
			{
				localTimerPulse->TickPulse.BindUObject(this, &UCellControl::CellDoSomething);
				UE_LOG(LogTemp, Warning, TEXT("We have binded bla"));
			}
	}
}


void UCellControl::CellDoSomething(FString string_a)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *string_a);
}

// Called when the game starts
void UCellControl::BeginPlay()
{
	Super::BeginPlay();

	FindSender();
	
}


// Called every frame
void UCellControl::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

