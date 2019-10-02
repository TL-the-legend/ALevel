// Fill out your copyright notice in the Description page of Project Settings.


#include "CellGeneratorAndController.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

// Sets default values
ACellGeneratorAndController::ACellGeneratorAndController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACellGeneratorAndController::GenerateCells()
{
	/*
	UWorld* World = GetWorld();
	uint32 foo = 0;
	for (uint32 i = 0; i < 5; i++) 
	{
		foo++;
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		FVector Location = { 100.f, 100.f, 0.f };
		FRotator Rotation = FRotator();
		ACell* myCellName = World->SpawnActor<ACell>(ClassToSpawn, Location, Rotation, SpawnParams);
		UE_LOG(LogTemp, Warning, TEXT("foo = %u; i = %u"), foo, i);
	}
	*/
	/**/
	//// Spawn actors and put their address into a 2D array
	UWorld* World = GetWorld();
	for (uint8 i = 0; i < height; i++) {
		FCellRow thisRow;
		CellCollections.Add(thisRow);
		UE_LOG(LogTemp, Warning, TEXT("heightloop = %u"), i);
		for (uint8 j = 0; j < width; j++) {	
			ACell* myNewCell = nullptr;
			if (World) {
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				FVector Location = { (float)i * 110.f, (float)j * 110.f, 0.f };
				FRotator Rotation = FRotator();
				myNewCell = World->SpawnActor<ACell>(ClassToSpawn, Location, Rotation, SpawnParams);
				UE_LOG(LogTemp, Warning, TEXT("Spawned"));
				CellCollections[i].CellAdrs.Add(myNewCell);
			}
			
			UE_LOG(LogTemp, Warning, TEXT("widthloop = %u"), j);
		}
	}
	//*/
	
}


void ACellGeneratorAndController::ObserveCells(ACell* ThisCell, uint8 X_Axis, uint8 Y_Axis)
{
	//// Initialize living and dead neighbours
	uint8 LivingNeighbours = 0;
	uint8 DeadNeighbours = 0;

	//// get the state of the current cell
	ECellState ThisCellState = ThisCell->ReturnState();

	//// Check neighbours
	/*
	OOO
	OXO
	OOO
	*/
	
	//// Decide which Neighbour Cells have to be observed
	if (X_Axis == 0)
	{
		if (Y_Axis == height - 1)
		{
			//// top left corner
			// check right
			if (RightCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
			// check bottom right
			if (BottomRightCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
			// check bottom
			if (BottomCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
		}
		else if (Y_Axis == 0)
		{
			//// bottom left corner
			// check right
			if (RightCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
			// check top right
			if (TopRightCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
			// check top
			if (TopCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
		}
		else
		{
			//// just left border
			// check right
			if (RightCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
			// check bottom right
			if (BottomRightCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
			// check bottom
			if (BottomCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
			// check top right
			if (TopRightCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
			// check top
			if (TopCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
		}
	}
	else if (X_Axis == width - 1)
	{
		if (Y_Axis == height - 1)
		{
			//// top right corner
			// check bottom left
			if (BottomLeftCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
			// check left
			if (LeftCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
			// check bottom
			if (BottomCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
		}
		else if (Y_Axis == 0)
		{
			//// bottom right corner
			// check top left
			if (TopLeftCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
			// check left
			if (LeftCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
			// check bottom
			if (TopCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
		}
		else
		{
			//// just right border
			// check bottom left
			if (BottomLeftCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
			// check left
			if (LeftCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
			// check bottom
			if (BottomCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
			// check top left
			if (TopLeftCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
			// check top 
			if (TopCell(X_Axis, Y_Axis) == ECellState::Alive)
			{
				++LivingNeighbours;
			}
			else
			{
				++DeadNeighbours;
			}
		}
	}
	else if (Y_Axis == 0)
	{
		//// just bottom border
		// check right 
		if (RightCell(X_Axis, Y_Axis) == ECellState::Alive)
		{
			++LivingNeighbours;
		}
		else
		{
			++DeadNeighbours;
		}
		// check left
		if (LeftCell(X_Axis, Y_Axis) == ECellState::Alive)
		{
			++LivingNeighbours;
		}
		else
		{
			++DeadNeighbours;
		}
		// check top right
		if (TopRightCell(X_Axis, Y_Axis) == ECellState::Alive)
		{
			++LivingNeighbours;
		}
		else
		{
			++DeadNeighbours;
		}
		// check top left
		if (TopLeftCell(X_Axis, Y_Axis) == ECellState::Alive)
		{
			++LivingNeighbours;
		}
		else
		{
			++DeadNeighbours;
		}
		// check top 
		if (TopCell(X_Axis, Y_Axis) == ECellState::Alive)
		{
			++LivingNeighbours;
		}
		else
		{
			++DeadNeighbours;
		}
	}
	else if (Y_Axis == height - 1)
	{
		//// just top border
		// check right 
		if (RightCell(X_Axis, Y_Axis) == ECellState::Alive)
		{
			++LivingNeighbours;
		}
		else
		{
			++DeadNeighbours;
		}
		// check left
		if (LeftCell(X_Axis, Y_Axis) == ECellState::Alive)
		{
			++LivingNeighbours;
		}
		else
		{
			++DeadNeighbours;
		}
		// check bottom right
		if (BottomRightCell(X_Axis, Y_Axis) == ECellState::Alive)
		{
			++LivingNeighbours;
		}
		else
		{
			++DeadNeighbours;
		}
		// check bottom left
		if (BottomLeftCell(X_Axis, Y_Axis) == ECellState::Alive)
		{
			++LivingNeighbours;
		}
		else
		{
			++DeadNeighbours;
		}
		// check bottom 
		if (BottomCell(X_Axis, Y_Axis) == ECellState::Alive)
		{
			++LivingNeighbours;
		}
		else
		{
			++DeadNeighbours;
		}
	}
	else
	{
		//// anywhere else on the map (non borders) so check all neighbours
		// check right 
		if (RightCell(X_Axis, Y_Axis) == ECellState::Alive)
		{
			++LivingNeighbours;
		}
		else
		{
			++DeadNeighbours;
		}
		// check left
		if (LeftCell(X_Axis, Y_Axis) == ECellState::Alive)
		{
			++LivingNeighbours;
		}
		else
		{
			++DeadNeighbours;
		}
		// check top right
		if (TopRightCell(X_Axis, Y_Axis) == ECellState::Alive)
		{
			++LivingNeighbours;
		}
		else
		{
			++DeadNeighbours;
		}
		// check top left
		if (TopLeftCell(X_Axis, Y_Axis) == ECellState::Alive)
		{
			++LivingNeighbours;
		}
		else
		{
			++DeadNeighbours;
		}
		// check top 
		if (TopCell(X_Axis, Y_Axis) == ECellState::Alive)
		{
			++LivingNeighbours;
		}
		else
		{
			++DeadNeighbours;
		}
		// check bottom right
		if (BottomRightCell(X_Axis, Y_Axis) == ECellState::Alive)
		{
			++LivingNeighbours;
		}
		else
		{
			++DeadNeighbours;
		}
		// check bottom left
		if (BottomLeftCell(X_Axis, Y_Axis) == ECellState::Alive)
		{
			++LivingNeighbours;
		}
		else
		{
			++DeadNeighbours;
		}
		// check bottom 
		if (BottomCell(X_Axis, Y_Axis) == ECellState::Alive)
		{
			++LivingNeighbours;
		}
		else
		{
			++DeadNeighbours;
		}
	}
	
	
	if (ThisCellState == ECellState::Alive) // If the cell is currently alive
	{

	}
	else // If the cell is dead
	{

	}
}

ECellState ACellGeneratorAndController::TopLeftCell(uint8 X_Axis, uint8 Y_Axis)
{
	//// return the state of the *function name* neighbour's state
	if (CellCollections[X_Axis - 1].CellAdrs[Y_Axis + 1]->ReturnState() == ECellState::Alive)
	{
		return ECellState::Alive;
	}
	else
	{
		return ECellState::Dead;
	}
}

ECellState ACellGeneratorAndController::TopCell(uint8 X_Axis, uint8 Y_Axis)
{
	//// return the state of the *function name* neighbour's state
	if (CellCollections[X_Axis].CellAdrs[Y_Axis + 1]->ReturnState() == ECellState::Alive)
	{
		return ECellState::Alive;
	}
	else
	{
		return ECellState::Dead;
	}
}

ECellState ACellGeneratorAndController::TopRightCell(uint8 X_Axis, uint8 Y_Axis)
{
	//// return the state of the *function name* neighbour's state
	if (CellCollections[X_Axis + 1].CellAdrs[Y_Axis + 1]->ReturnState() == ECellState::Alive)
	{
		return ECellState::Alive;
	}
	else
	{
		return ECellState::Dead;
	}
}

ECellState ACellGeneratorAndController::LeftCell(uint8 X_Axis, uint8 Y_Axis)
{
	//// return the state of the *function name* neighbour's state
	if (CellCollections[X_Axis - 1].CellAdrs[Y_Axis]->ReturnState() == ECellState::Alive)
	{
		return ECellState::Alive;
	}
	else
	{
		return ECellState::Dead;
	}
}

ECellState ACellGeneratorAndController::RightCell(uint8 X_Axis, uint8 Y_Axis)
{
	//// return the state of the *function name* neighbour's state
	if (CellCollections[X_Axis + 1].CellAdrs[Y_Axis]->ReturnState() == ECellState::Alive)
	{
		return ECellState::Alive;
	}
	else
	{
		return ECellState::Dead;
	}
}

ECellState ACellGeneratorAndController::BottomLeftCell(uint8 X_Axis, uint8 Y_Axis)
{
	//// return the state of the *function name* neighbour's state
	if (CellCollections[X_Axis - 1].CellAdrs[Y_Axis - 1]->ReturnState() == ECellState::Alive)
	{
		return ECellState::Alive;
	}
	else
	{
		return ECellState::Dead;
	}
}

ECellState ACellGeneratorAndController::BottomCell(uint8 X_Axis, uint8 Y_Axis)
{
	//// return the state of the *function name* neighbour's state
	if (CellCollections[X_Axis].CellAdrs[Y_Axis - 1]->ReturnState() == ECellState::Alive)
	{
		return ECellState::Alive;
	}
	else
	{
		return ECellState::Dead;
	}
}

ECellState ACellGeneratorAndController::BottomRightCell(uint8 X_Axis, uint8 Y_Axis)
{
	//// return the state of the *function name* neighbour's state
	if (CellCollections[X_Axis + 1].CellAdrs[Y_Axis - 1]->ReturnState() == ECellState::Alive)
	{
		return ECellState::Alive;
	}
	else
	{
		return ECellState::Dead;
	}
}

// Called when the game starts or when spawned
void ACellGeneratorAndController::BeginPlay()
{
	Super::BeginPlay();

	GenerateCells();
	//UEnum State = CellCollections[0].CellAdrs[0]->ReturnState();
	ECellState State = CellCollections[0].CellAdrs[0]->ReturnState();
	
	if (State == ECellState::Alive) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Alive"));
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Dead"));
	}
}

// Called every frame
void ACellGeneratorAndController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

