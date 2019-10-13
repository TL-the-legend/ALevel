// Fill out your copyright notice in the Description page of Project Settings.


#include "Cell.h"

// Sets default values
ACell::ACell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh"));
	MyMesh->SetupAttachment(RootComponent);
	RootComponent = MyMesh;


	AliveMaterial = CreateDefaultSubobject<UMaterial>(TEXT("AliveMaterial"));
	DeadMaterial = CreateDefaultSubobject<UMaterial>(TEXT("DeadMaterial"));
	ChangeMaterial = CreateDefaultSubobject<UMaterial>(TEXT("ChangeMaterial"));

}

ECellState ACell::ReturnState()
{
	return State;
}

void ACell::LoadNextState(ECellState NextState)
{
	NextNewState = NextState;
}

void ACell::UpdateState()
{
	if (NextNewState != State) 
	{
		if (NextNewState == ECellState::Alive)
		{
			State = ECellState::Alive;
			ChangeMaterialAlive();
		}
		else
		{
			State = ECellState::Dead;
			ChangeMaterialDead();
		}
	}
}

void ACell::ChangeMaterialAlive()
{
	MyMesh->SetMaterial(0, AliveMaterial);
}

void ACell::ChangeMaterialDead()
{
	MyMesh->SetMaterial(0, DeadMaterial);
}

void ACell::SetUpMaterial()
{
	MyMesh->SetMaterial(0, AliveMaterial);
}

// Called when the game starts or when spawned
void ACell::BeginPlay()
{
	Super::BeginPlay();
	SetUpMaterial();
}

// Called every frame
void ACell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

