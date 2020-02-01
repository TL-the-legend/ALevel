// Fill out your copyright notice in the Description page of Project Settings.


#include "CellChanger.h"

// Sets default values for this component's properties
UCellChanger::UCellChanger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCellChanger::loading_InputComponent()
{
	
	// Codes for binding keys
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Error, TEXT("InputComponent found"));
		//bind keys
		InputComponent->BindAction("ChangeCellsState", IE_Pressed, this, &UCellChanger::LineTraceAndChangeState);
		InputComponent->BindAction("ChangeCellsState", IE_Released, this, &UCellChanger::ChangeStateBool);
		InputComponent->BindAction("ToggleTick", IE_Pressed, this, &UCellChanger::ToggleTickGaC);
		InputComponent->BindAction("DelayTimeZero", IE_Pressed, this, &UCellChanger::DelayTimeZeroGaC);
		InputComponent->BindAction("SetDefaultDelayTime", IE_Pressed, this, &UCellChanger::SetDefaultDelayTimeGaC);
		InputComponent->BindAction("DefaultTimeTimesTwo", IE_Pressed, this, &UCellChanger::DefaultTimeTimesTwoGaC);
		InputComponent->BindAction("DefaultTimeDevideTwo", IE_Pressed, this, &UCellChanger::DefaultTimeDevideTwoGaC);

		InputComponentLoaded = true;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s cant find InputHandle"), *GetOwner()->GetName());
	}
}

void UCellChanger::LineTraceAndChangeState()
{
	//// To prevent changing state each frame over and over again when the use is still holding the key

		//// Get the player's view point
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	// Get the data into PlayerViewPointLocation and PlayerViewPointRotation
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	//// Calculate end of the line trace
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * DistanceReach;

	//// Draw Debugline (just for debuging)
	//DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 5.f);

	//// Ray Cast
	FHitResult HitCell;
	FCollisionQueryParams CollisionParams;
	// Line trace and see what object did it hit
	if (GetWorld()->LineTraceSingleByChannel(HitCell, PlayerViewPointLocation, LineTraceEnd, ECC_Visibility, CollisionParams))
	{
		// if something got hit then do something
		AActor* HitActor = HitCell.GetActor();
		if (ensureMsgf(HitActor, TEXT("HitActor nullptr")))
		{
			// if the something is one of the cells then do something
			if (ACell* TheCell = Cast<ACell>(HitCell.Actor))
			{
				UE_LOG(LogTemp, Warning, TEXT("Hitting: %s"), *TheCell->GetName());
				// call FlipState to flip state
				TheCell->FlipState();
				// disable the change state function until the user release the key
				//AllowChangeState = false;
			}
		}
	}
}

void UCellChanger::ChangeStateBool()
{
	AllowChangeState = true;
}

AActor* UCellChanger::FindCellGeneratorAndController()
{
	// Getting the adress of the actor
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.

		AActor* ActorI = *ActorItr;
		UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *ActorI->GetFName().ToString())
			if (ActorI->GetFName().ToString().Contains(TEXT("CellGeneratorAndController")))
			{
				// update CellGaC and stop the loop when the actor is found
				CellGaC = ActorI;
				break;
			}
	}
	if (CellGaC) 
	{
		return CellGaC;
	}
	else
	{
		return nullptr;
	}
	
}


void UCellChanger::ToggleTickGaC()
{
	// Cast from AActor to ACellGeneratorAndController
	ACellGeneratorAndController* Cell = Cast<ACellGeneratorAndController>(CellGaC);
	// Call ToggleTick function from ACellGeneratorAndController class
	Cell->ToggleTick();
}

void UCellChanger::DelayTimeZeroGaC()
{
	// Cast from AActor to ACellGeneratorAndController
	ACellGeneratorAndController* Cell = Cast<ACellGeneratorAndController>(CellGaC);
	// Call DelayTimeZero function from ACellGeneratorAndController class
	Cell->DelayTimeZero();
}

void UCellChanger::SetDefaultDelayTimeGaC()
{
	// Cast from AActor to ACellGeneratorAndController
	ACellGeneratorAndController* Cell = Cast<ACellGeneratorAndController>(CellGaC);
	// Call SetDefaultDelayTime function from ACellGeneratorAndController class
	Cell->SetDefaultDelayTime();
}

void UCellChanger::DefaultTimeTimesTwoGaC()
{
	// Cast from AActor to ACellGeneratorAndController
	ACellGeneratorAndController* Cell = Cast<ACellGeneratorAndController>(CellGaC);
	// Call DefaultTimeTimesTwo function from ACellGeneratorAndController class
	Cell->DefaultTimeTimesTwo();
}

void UCellChanger::DefaultTimeDevideTwoGaC()
{
	// Cast from AActor to ACellGeneratorAndController
	ACellGeneratorAndController* Cell = Cast<ACellGeneratorAndController>(CellGaC);
	// Call DefaultTimeDevideTwo function from ACellGeneratorAndController class
	Cell->DefaultTimeDevideTwo();
}



// Called when the game starts
void UCellChanger::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//// Call function to check if the input component is loaded
	//loading_InputComponent();
	// Get the Address of the CellGeneratorAndController actor
	CellGaC = FindCellGeneratorAndController();
	//ACellGeneratorAndController* CellGaCRef = Cast<ACellGeneratorAndController>(CellGaC);
}


// Called every frame
void UCellChanger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	//// Line Trace and change state
	//LineTraceAndChangeState();
	//ACellGeneratorAndController* CellRef = Cast<ACellGeneratorAndController>(CellGaC);

	//// Load InputComponent and bindkeys after all the cells are generated
	// Cast from AActor to ACellGeneratorAndController
	ACellGeneratorAndController* CellGaCRef = Cast<ACellGeneratorAndController>(CellGaC);
	if (CellGaCRef->ReturnCellGenerated() && InputComponentLoaded == false)
	{
		loading_InputComponent(); 
	}

}

