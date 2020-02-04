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

// BP test function
void ACellGeneratorAndController::BPtestFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("BP test function called"));
}


void ACellGeneratorAndController::GenerateCells(int32 PassedInHeight, int32 PassedInWidth)
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
	height = PassedInHeight;
	width = PassedInWidth;

	//// Spawn actors and put their address into a 2D array
	// i is in CellCollection therefore i = height = X_Axis
	// j is in CellAdrs therefore j = width = Y_Axis
	UWorld* World = GetWorld();
	for (uint8 i = 0; i < height; i++)
	{
		FCellRow thisRow;
		CellCollections.Add(thisRow);
		UE_LOG(LogTemp, Warning, TEXT("heightloop = %u"), i);
		for (uint8 j = 0; j < width; j++) 
		{	
			ACell* myNewCell = nullptr;
			if (World) {

				/////////////////////Normal SpawnActor/////////////////////

				// Spawn actors
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				FVector Location = { 0.f, static_cast<float>(i * 110.0f), static_cast<float>(j * 110.0f) };
				//FVector Location = { (float)i * 110.f, (float)j * 110.f, 0.f };
				FRotator Rotation = FRotator();
				myNewCell = World->SpawnActor<ACell>(ClassToSpawn, Location, Rotation, SpawnParams);
				UE_LOG(LogTemp, Warning, TEXT("Spawned"));
				CellCollections[i].CellAdrs.Add(myNewCell);

				
				// Add Mesh
				//static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/World/Cube.Cube'"));
				//static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshOb_torus(TEXT("StaticMesh'/Engine/EditorShapes/Meshes/Shape_Torus.Shape_Torus'"));
				//UStaticMesh* Asset;// = MeshAsset.Object;
				/*
				UInstancedStaticMeshComponent* ISMComp = NewObject<UInstancedStaticMeshComponent>(myNewCell);
				ISMComp->RegisterComponent();
				ISMComp->SetStaticMesh(MeshAsset);
				ISMComp->SetFlags(RF_Transactional);
				myNewCell->AddInstanceComponent(ISMComp);
				FTransform Transform = myNewCell->GetTransform();
				ISMComp->AddInstance(Transform);
				*/


				/////////////////////Spawn Instance/////////////////////

			}
			
			UE_LOG(LogTemp, Warning, TEXT("widthloop = %u"), j);
		}
	}
	//*/
	CellGenerated = true;
	GameStarted = true;
	UE_LOG(LogTemp, Warning, TEXT("height = %u"), height);
	UE_LOG(LogTemp, Warning, TEXT("width = %u"), width);

}


bool ACellGeneratorAndController::ReturnCellGenerated()
{
	return CellGenerated;
}

void ACellGeneratorAndController::ObserveCells(ACell* ThisCell, uint8 X_Axis, uint8 Y_Axis)
{
	//// Initialize living and dead neighbours
	uint8 LivingNeighbours = 0;
	//uint8 DeadNeighbours = 0;

	//// get the state of the current cell
	ECellState ThisCellState = ThisCell->ReturnState();

	//// Check neighbours
	/*
	OOO
	OXO
	OOO
	*/
	
	//// Decide which Neighbour Cells have to be observed and update the total dead or alive neighbours
	if (X_Axis == 0)
	{
		if (Y_Axis == 0) // Bottom Left of the map T,TR,R
		{			
			LivingNeighbours = CheckTopCell(LivingNeighbours, X_Axis, Y_Axis);
			LivingNeighbours = CheckTopRightCell(LivingNeighbours, X_Axis, Y_Axis);
			LivingNeighbours = CheckRightCell(LivingNeighbours, X_Axis, Y_Axis);			
		}
		else if (Y_Axis == height - 1) // Top Left of the map R,BR,B
		{			
			LivingNeighbours = CheckRightCell(LivingNeighbours, X_Axis, Y_Axis);
			LivingNeighbours = CheckBottomRightCell(LivingNeighbours, X_Axis, Y_Axis);
			LivingNeighbours = CheckBottomCell(LivingNeighbours, X_Axis, Y_Axis);
		}
		else // Rest of the Left side of the map T,TR,R,BR,B
		{			
			LivingNeighbours = CheckTopCell(LivingNeighbours, X_Axis, Y_Axis);
			LivingNeighbours = CheckTopRightCell(LivingNeighbours, X_Axis, Y_Axis);
			LivingNeighbours = CheckRightCell(LivingNeighbours, X_Axis, Y_Axis);
			LivingNeighbours = CheckBottomRightCell(LivingNeighbours, X_Axis, Y_Axis);
			LivingNeighbours = CheckBottomCell(LivingNeighbours, X_Axis, Y_Axis);			
		}
	}
	else if (X_Axis == width - 1) 
	{
		if (Y_Axis == 0) // Bottom Right of the map L,TL,T
		{
			LivingNeighbours = CheckLeftCell(LivingNeighbours, X_Axis, Y_Axis);
			LivingNeighbours = CheckTopLeftCell(LivingNeighbours, X_Axis, Y_Axis);
			LivingNeighbours = CheckTopCell(LivingNeighbours, X_Axis, Y_Axis);
		}
		else if (Y_Axis == height - 1) // Top Right of the map L,BL,B
		{			
			LivingNeighbours = CheckLeftCell(LivingNeighbours, X_Axis, Y_Axis);
			LivingNeighbours = CheckBottomLeftCell(LivingNeighbours, X_Axis, Y_Axis);
			LivingNeighbours = CheckBottomCell(LivingNeighbours, X_Axis, Y_Axis);
		}
		else // Rest of the Right side of the map T,TL,L,BL,B
		{
						LivingNeighbours = CheckTopCell(LivingNeighbours, X_Axis, Y_Axis);
			LivingNeighbours = CheckTopLeftCell(LivingNeighbours, X_Axis, Y_Axis);
			LivingNeighbours = CheckLeftCell(LivingNeighbours, X_Axis, Y_Axis);
			LivingNeighbours = CheckBottomLeftCell(LivingNeighbours, X_Axis, Y_Axis);
			LivingNeighbours = CheckBottomCell(LivingNeighbours, X_Axis, Y_Axis);			
		}
	}
	else if (Y_Axis == 0) // Rest of the Bottom side of the map L,TL,T,TR,R
	{		
		LivingNeighbours = CheckLeftCell(LivingNeighbours, X_Axis, Y_Axis);
		LivingNeighbours = CheckTopLeftCell(LivingNeighbours, X_Axis, Y_Axis);
		LivingNeighbours = CheckTopCell(LivingNeighbours, X_Axis, Y_Axis);
		LivingNeighbours = CheckTopRightCell(LivingNeighbours, X_Axis, Y_Axis);
		LivingNeighbours = CheckRightCell(LivingNeighbours, X_Axis, Y_Axis);		
	}
	else if (Y_Axis == height - 1) // Rest of the Top side of the map L,BL,B,BR,R
	{		
		LivingNeighbours = CheckLeftCell(LivingNeighbours, X_Axis, Y_Axis);
		LivingNeighbours = CheckBottomLeftCell(LivingNeighbours, X_Axis, Y_Axis);
		LivingNeighbours = CheckBottomCell(LivingNeighbours, X_Axis, Y_Axis);
		LivingNeighbours = CheckBottomRightCell(LivingNeighbours, X_Axis, Y_Axis);
		LivingNeighbours = CheckRightCell(LivingNeighbours, X_Axis, Y_Axis);		
	}
	else // Rest of the map that is non-edge TL,T,TR,L,R,BL,B,BR
	{		
		LivingNeighbours = CheckTopLeftCell(LivingNeighbours, X_Axis, Y_Axis);
		LivingNeighbours = CheckTopCell(LivingNeighbours, X_Axis, Y_Axis);
		LivingNeighbours = CheckTopRightCell(LivingNeighbours, X_Axis, Y_Axis);
		LivingNeighbours = CheckLeftCell(LivingNeighbours, X_Axis, Y_Axis);
		LivingNeighbours = CheckRightCell(LivingNeighbours, X_Axis, Y_Axis);
		LivingNeighbours = CheckBottomLeftCell(LivingNeighbours, X_Axis, Y_Axis);
		LivingNeighbours = CheckBottomCell(LivingNeighbours, X_Axis, Y_Axis);
		LivingNeighbours = CheckBottomRightCell(LivingNeighbours, X_Axis, Y_Axis);		
	}
	
	//// Decide which Neighbour Cells have to be observed and update the total dead or alive neighbours
	/*
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
	*/
	
	//// Load the next state of the cell
	if (ThisCellState == ECellState::Alive) // If the cell is currently alive
	{
		if (LivingNeighbours < 2) // Any live cell with fewer than two live neighbours dies, as if by underpopulation.
		{
			ThisCell->LoadNextState(ECellState::Dead);
		}
		else if (LivingNeighbours == 2 || LivingNeighbours == 3) //Any live cell with two or three live neighbours lives on to the next generation.
		{
			ThisCell->LoadNextState(ECellState::Alive);
		}
		else //Any live cell with more than three live neighbours dies, as if by overpopulation.
		{
			ThisCell->LoadNextState(ECellState::Dead);
		}
	}
	else // If the cell is dead
	{
		if (LivingNeighbours == 3) // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
		{
			ThisCell->LoadNextState(ECellState::Alive);
		}
	}
}

void ACellGeneratorAndController::UpdateCellState(ACell* myCell)
{
	myCell->UpdateState();
}

///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////BETWEEN HEREvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv//////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

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
///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////BETWEEN HERE^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

uint8 ACellGeneratorAndController::CheckTopLeftCell(uint8 LivingNeighbours, uint8 X_Axis, uint8 Y_Axis)
{
	// update LivingNeighbours
	if (TopLeftCell(X_Axis, Y_Axis) == ECellState::Alive)
	{
		++LivingNeighbours;
	}
	return LivingNeighbours;
}

uint8 ACellGeneratorAndController::CheckTopCell(uint8 LivingNeighbours, uint8 X_Axis, uint8 Y_Axis)
{
	// update LivingNeighbours
	if (TopCell(X_Axis, Y_Axis) == ECellState::Alive)
	{
		++LivingNeighbours;
	}
	return LivingNeighbours;
}

uint8 ACellGeneratorAndController::CheckTopRightCell(uint8 LivingNeighbours, uint8 X_Axis, uint8 Y_Axis)
{
	// update LivingNeighbours
	if (TopRightCell(X_Axis, Y_Axis) == ECellState::Alive)
	{
		++LivingNeighbours;
	}
	return LivingNeighbours;
}

uint8 ACellGeneratorAndController::CheckLeftCell(uint8 LivingNeighbours, uint8 X_Axis, uint8 Y_Axis)
{
	// update LivingNeighbours
	if (LeftCell(X_Axis, Y_Axis) == ECellState::Alive)
	{
		++LivingNeighbours;
	}
	return LivingNeighbours;
}

uint8 ACellGeneratorAndController::CheckRightCell(uint8 LivingNeighbours, uint8 X_Axis, uint8 Y_Axis)
{
	// update LivingNeighbours
	if (RightCell(X_Axis, Y_Axis) == ECellState::Alive)
	{
		++LivingNeighbours;
	}
	return LivingNeighbours;
}

uint8 ACellGeneratorAndController::CheckBottomLeftCell(uint8 LivingNeighbours, uint8 X_Axis, uint8 Y_Axis)
{
	// update LivingNeighbours
	if (BottomLeftCell(X_Axis, Y_Axis) == ECellState::Alive)
	{
		++LivingNeighbours;
	}
	return LivingNeighbours;
}

uint8 ACellGeneratorAndController::CheckBottomCell(uint8 LivingNeighbours, uint8 X_Axis, uint8 Y_Axis)
{
	// update LivingNeighbours
	if (BottomCell(X_Axis, Y_Axis) == ECellState::Alive)
	{
		++LivingNeighbours;
	}
	return LivingNeighbours;
}

uint8 ACellGeneratorAndController::CheckBottomRightCell(uint8 LivingNeighbours, uint8 X_Axis, uint8 Y_Axis)
{
	// update LivingNeighbours
	if (BottomRightCell(X_Axis, Y_Axis) == ECellState::Alive)
	{
		++LivingNeighbours;
	}
	return LivingNeighbours;
}

void ACellGeneratorAndController::AllCellTick()
{
	//// First Step
	// Tell each cell what their next state will be
	for (uint8 i = 0; i < height; i++) {
		for (uint8 j = 0; j < width; j++) 
		{
			ACell* ThisCell = CellCollections[i].CellAdrs[j];
			ObserveCells(ThisCell, i, j);
		}
	}

	//// Second Step
	// Tell each cell to update their state
	for (uint8 i = 0; i < height; i++) {
		for (uint8 j = 0; j < width; j++)
		{
			ACell* ThisCell = CellCollections[i].CellAdrs[j];
			UpdateCellState(ThisCell);
		}
	}
}
void ACellGeneratorAndController::ToggleTick()
{
	// switch between true and false
	if (AllowTick == true)
	{
		AllowTick = false;
	}
	else 
	{
		AllowTick = true;
	}
}

//void ACellGeneratorAndController::loading_InputComponent()
//{
//	UInputComponent* InputComponent;
//	InputComponent = ->FindComponentByClass<UInputComponent>();
//	InputComponent->BindAction("ToggleTick", IE_Pressed, this, &ACellGeneratorAndController::ToggleTick);
//}


//
//ACell* ACellGeneratorAndController::ReturnCellArress(AActor* CellAActorAdress)
//{
//	ACell* TheCell = nullptr;
//	// Find CellNumber
//	int16 CellNumber = NULL;
//	// 
//
//	if (CellNumber)
//	{
//		// Find row
//		int8 row = CellNumber / height;
//		// FInd column
//		int8 column = CellNumber % width;
//		// Get the address from the array
//		TheCell = CellCollections[row].CellAdrs[column];
//		return TheCell;
//	}
//
//}

void ACellGeneratorAndController::DelayTimeZero()
{
	TimerDelayTime = 0.0f;
}

void ACellGeneratorAndController::SetDefaultDelayTime()
{
	TimerDelayTime = 0.5f;
}

void ACellGeneratorAndController::DefaultTimeTimesTwo()
{
	TimerDelayTime = TimerDelayTime * 2;
}

void ACellGeneratorAndController::DefaultTimeDevideTwo()
{
	TimerDelayTime = TimerDelayTime / 2;
}

// Called when the game starts or when spawned
void ACellGeneratorAndController::BeginPlay()
{
	Super::BeginPlay();

	//GenerateCells(height, width);
	
	//loading_InputComponent();
}

// Called every frame
void ACellGeneratorAndController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Won't do anything if the game hasn't started and the cells aren't generated to prevent array out of range error when pressing toggletick before everything is done
	if (GameStarted) {
		if (AllowTick)
		{
			if (TimerDelayTime >= DeltaTime) //// if the the user-set timer is larger or equal to the frame rate, then this will tick with the user set time between each pulse
			{
				timer += DeltaTime;

				if (timer >= TimerDelayTime)
				{
					float timerLeftOvers = timer - TimerDelayTime;

					UE_LOG(LogTemp, Warning, TEXT("timer beep Normal TimerDelayTime"));
					AllCellTick();

					timer = timerLeftOvers;
				}
			}
			else //// if the user set timer is too fast then it will tick according to the frame speed
			{
				UE_LOG(LogTemp, Warning, TEXT("timer beep Temp TimerDelayTime"));
				AllCellTick();
			}
		}
	}
}

