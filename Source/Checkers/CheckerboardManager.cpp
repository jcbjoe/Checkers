// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckerboardManager.h"


// Sets default values
ACheckerboardManager::ACheckerboardManager(): selectedX(0), selectedY(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACheckerboardManager::BeginPlay()
{
	Super::BeginPlay();

	createCheckerboard();

	if (GEngine){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
	}
	
}

// Called every frame
void ACheckerboardManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AGridPiece* ACheckerboardManager::getGridPieceAt(int x, int y) {
	return gridPieceArray[x][y];
}

ACheckerPiece* ACheckerboardManager::getCheckerPieceAt(int x, int y) {
	return checkerPieceArray[x][y];
}

void ACheckerboardManager::setSelected(int x, int y) {
	getGridPieceAt(selectedX, selectedY)->setSelected(false);

	selectedX = x;
	selectedY = y;
	
	AGridPiece* newSelected = getGridPieceAt(selectedX, selectedY);
	removePossibleMoves();
	if(hasPieceOnTop(newSelected)){
		newSelected->setSelected(true);
		ACheckerPiece* checkerPiece = getCheckerPieceAt(selectedX, selectedY);
		int player = checkerPiece->getPlayer();
		bool isKing = checkerPiece->isKing();
		showPossibleMoves(player, isKing);
	}
}

void ACheckerboardManager::showPossibleMoves(int player, bool isKing) {
	AGridPiece* gridPiece;
	if (isKing) {

	} else {
		if (player == 0) {
			//--- So we are on the Right hand side! So we need to go right so x  -1
			if (!(selectedY == 0)) {
				gridPiece = getGridPieceAt(selectedX - 1, selectedY - 1);
				if (hasPieceOnTop(gridPiece)) {
					if (getCheckerPieceOnTop(gridPiece)->getPlayer() != player) {
						if ((selectedY -1) < 0) {
							AGridPiece* JumpOverMove = getGridPieceAt(selectedX - 2, selectedY - 2);
							JumpOverMove->setTextureHighlight(true);
							possibleMoveGridPieces.push_back(JumpOverMove);
						}
					}
				} else {
					gridPiece->setTextureHighlight(true);
					possibleMoveGridPieces.push_back(gridPiece);
				}
			}
			if (!(selectedY == (GRID_SIZE - 1))) {
				gridPiece = getGridPieceAt(selectedX - 1, selectedY + 1);
				if (hasPieceOnTop(gridPiece)) {
					if (getCheckerPieceOnTop(gridPiece)->getPlayer() != player) {
						if ((selectedY + 1) >= (GRID_SIZE - 1)) {
							AGridPiece* JumpOverMove = getGridPieceAt(selectedX - 2, selectedY + 2);
							JumpOverMove->setTextureHighlight(true);
							possibleMoveGridPieces.push_back(JumpOverMove);
						}
					}
				} else {
					gridPiece->setTextureHighlight(true);
					possibleMoveGridPieces.push_back(gridPiece);
				}
			}
		} else {
			//--- """" Left side going left x + 1
			if (!(selectedY == 0)) {
				gridPiece = getGridPieceAt(selectedX + 1, selectedY - 1);
				if (hasPieceOnTop(gridPiece)) {
					if (getCheckerPieceOnTop(gridPiece)->getPlayer() != player) {
						if ((selectedY - 1) < 0) {
							AGridPiece* JumpOverMove = getGridPieceAt(selectedX + 2, selectedY - 2);
							JumpOverMove->setTextureHighlight(true);
							possibleMoveGridPieces.push_back(JumpOverMove);
						}
					}
				} else {
					gridPiece->setTextureHighlight(true);
					possibleMoveGridPieces.push_back(gridPiece);
				}
			}
			if (!(selectedY == (GRID_SIZE - 1))) {
				gridPiece = getGridPieceAt(selectedX + 1, selectedY + 1);
				if (hasPieceOnTop(gridPiece)) {
					if (getCheckerPieceOnTop(gridPiece)->getPlayer() != player) {
						if ((selectedY + 1) >= (GRID_SIZE - 1)) {
							AGridPiece* JumpOverMove = getGridPieceAt(selectedX + 2, selectedY + 2);
							JumpOverMove->setTextureHighlight(true);
							possibleMoveGridPieces.push_back(JumpOverMove);
						}
					}
				} else {
					gridPiece->setTextureHighlight(true);
					possibleMoveGridPieces.push_back(gridPiece);
				}
			}
		}
	}
}

void ACheckerboardManager::removePossibleMoves() {
	for (AGridPiece* gridPiece : possibleMoveGridPieces) {
		gridPiece->setTextureHighlight(false);
	}
	possibleMoveGridPieces.clear();
}

void ACheckerboardManager::createCheckerboard() {
	bool colourChanger = false;
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			//--- Spawn grid piece
			AGridPiece* gridPiece_ = GetWorld()->SpawnActor<AGridPiece>(FVector(i * 400, j * 400, 0.0), FRotator(0.0, 0.0, 0.0), FActorSpawnParameters());
			int newX = GRID_SIZE - i - 1;
			if (colourChanger) 
				gridPiece_->passVariables(newX, j, 0, this);
			else
				gridPiece_->passVariables(newX, j, 1, this);
			gridPieceArray[newX][j] = gridPiece_;
			

			if ((i == 0 || i == 1 || i == 2 || i == (GRID_SIZE - 1) || i == (GRID_SIZE - 2) || i == (GRID_SIZE - 3)) && colourChanger) {
				//--- Spawn player pieces
				ACheckerPiece* checkerPiece_ = GetWorld()->SpawnActor<ACheckerPiece>(FVector(i * 400, j * 400, 100), FRotator(0.0, 0.0, 0.0), FActorSpawnParameters());
				checkerPieceArray[newX][j] = checkerPiece_;

				if (i == 0 || i == 1 || i == 2) {
					//--- Player 0
					checkerPiece_->passVariables(newX, j, 0, this);
				} else {
					//--- Player 1
					checkerPiece_->passVariables(newX, j, 1, this);
				}
			} else {
				checkerPieceArray[newX][j] = nullptr;
			}

			colourChanger = !colourChanger;
		}
		colourChanger = !colourChanger;
	}
}

bool ACheckerboardManager::hasPieceOnTop(AGridPiece* gridPiece) {
	int x = gridPiece->getX();
	int y = gridPiece->getY();
	ACheckerPiece* piece = checkerPieceArray[x][y];
	if (piece == nullptr)
		return false;
	else
		return true;
}

ACheckerPiece* ACheckerboardManager::getCheckerPieceOnTop(AGridPiece* gridPiece) {
	int x = gridPiece->getX();
	int y = gridPiece->getY();
	return checkerPieceArray[x][y];
}