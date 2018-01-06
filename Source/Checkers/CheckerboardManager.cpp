// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckerboardManager.h"


// Sets default values
ACheckerboardManager::ACheckerboardManager(): selectedX(0), selectedY(0), pieceMoving(false)
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

	if (pieceMoving) {

		float easingAmount = 0.05;
		if ((pieceToMoveTo != nullptr) && (checkerPieceMoving != nullptr)) {
			float xDistance = pieceToMoveTo->GetActorLocation().X - checkerPieceMoving->GetActorLocation().X;
			float yDistance = pieceToMoveTo->GetActorLocation().Y - checkerPieceMoving->GetActorLocation().Y;
			float distance = FGenericPlatformMath::Sqrt(xDistance * xDistance + yDistance * yDistance);
			if (distance > 1) {
				checkerPieceMoving->SetActorLocation(
					FVector(
						checkerPieceMoving->GetActorLocation().X + xDistance * easingAmount,
						checkerPieceMoving->GetActorLocation().Y + yDistance * easingAmount,
						checkerPieceMoving->GetActorLocation().Z
					)
				);
			} else {
				checkerPieceArray[checkerPieceMoving->getX()][checkerPieceMoving->getY()] = nullptr;
				checkerPieceMoving->setXY(pieceToMoveTo->getX(), pieceToMoveTo->getY());
				checkerPieceArray[checkerPieceMoving->getX()][checkerPieceMoving->getY()] = checkerPieceMoving;
				pieceMoving = false;
			}
		}

	}

}

AGridPiece* ACheckerboardManager::getGridPieceAt(int x, int y) {
	return gridPieceArray[x][y];
}

ACheckerPiece* ACheckerboardManager::getCheckerPieceAt(int x, int y) {
	return checkerPieceArray[x][y];
}

void ACheckerboardManager::onClicked(int x, int y) {
	if (!pieceMoving) {
		//--- Get old selected grid piece and unselect it.
		AGridPiece* oldSelectedCheckerPiece = getGridPieceAt(selectedX, selectedY);
		oldSelectedCheckerPiece->setSelected(false);

		//--- Change selected vars
		selectedX = x;
		selectedY = y;

		//--- Grab new selected grid piece
		AGridPiece* newSelected = getGridPieceAt(selectedX, selectedY);
		//--- Grab our new checker piece
		ACheckerPiece* checkerPiece = getCheckerPieceAt(selectedX, selectedY);
		if (hasPieceOnTop(newSelected)) {
			//--- Remove old possible moves
			removePossibleMoves();
			//--- If there is a checker piece on top of the grid piece we have selected, remember you can select a grid piece by clicking the checker pawn too
			newSelected->setSelected(true);
			//--- Grab side and if they are a king
			int player = checkerPiece->getPlayer();
			bool isKing = checkerPiece->isKing();
			//--- Show the possible moves the player can make
			showPossibleMoves(player, isKing);
		}
		else {
			if (vectorContains(possibleMoveGridPieces, newSelected)) {
				//--- Move Piece
				if (!pieceMoving) {
					checkerPieceMoving = getCheckerPieceOnTop(oldSelectedCheckerPiece);
					pieceToMoveTo = newSelected;
					pieceMoving = true;
					removePossibleMoves();
				}

			}
		}
	}
}

void ACheckerboardManager::showPossibleMoves(int player, bool isKing) {
	//--- Gets a bit complicated here
	if (isKing) {

	} else {
		//--- Check which player is moving
		if (player == 0) {
			//--- So we are on the Right side going LEFT! So we need to go right so x  -1
			//--- This is the BOTTOM highlight
			//--- Check that the selected piece is not on the bottom of the grid
			if (!(selectedY == 0)) {
				AGridPiece* leftBottom = getGridPieceAt(selectedX - 1, selectedY - 1);
				//--- Check if we need to jump over or not
				if (hasPieceOnTop(leftBottom)) {
					//--- JUMP
					if (getCheckerPieceOnTop(leftBottom)->getPlayer() != player) {

						int JumpOverX = selectedX - 2;
						int JumpoverY = selectedY - 2;

						//--- Make sure our y is not less than 0 (off the board)
						if (JumpoverY >= 0) {

							AGridPiece* JumpOverMove = getGridPieceAt(JumpOverX, JumpoverY);

							//--- Is there a piece there?
							if (!hasPieceOnTop(JumpOverMove)) {
								JumpOverMove->setTextureHighlight(true);
								possibleMoveGridPieces.push_back(JumpOverMove);
							}
						}
					}
				} else {
					//--- If no piece on top just normally highlight
					leftBottom->setTextureHighlight(true);
					possibleMoveGridPieces.push_back(leftBottom);
				}
			}
			//--- This is the TOP highlight
			//--- Check the selected piece is not on the top of the grid, its -1 because of the loop that builds the grid starts at 0
			if (!(selectedY == (GRID_SIZE - 1))) {
				//--- Left  top Piece
				AGridPiece* leftTop = getGridPieceAt(selectedX - 1, selectedY + 1);
				//--- is there a piece on top?
				if (hasPieceOnTop(leftTop)) {
					//--- Is it our own?
					if (getCheckerPieceOnTop(leftTop)->getPlayer() != player) {

						//--- Work out jump over position
						int JumpOverX = selectedX - 2;
						int JumpoverY = selectedY + 2;

						//--- Make sure our Y is not off the top of the board
						if (JumpoverY <= (GRID_SIZE - 1)) {

							AGridPiece* JumpOverMove = getGridPieceAt(JumpOverX, JumpoverY);

							//--- Is there a piece there?
							if (!hasPieceOnTop(JumpOverMove)) {
								JumpOverMove->setTextureHighlight(true);
								possibleMoveGridPieces.push_back(JumpOverMove);
							}
						}
					}
				} else {
					//--- If no piece on top just normally highlight
					leftTop->setTextureHighlight(true);
					possibleMoveGridPieces.push_back(leftTop);
				}
			}
		} else {
			//--- WE are on the LEFT side going RIGHT
			if (!(selectedY == 0)) {
				//--- This is the BOTTOM highlight
				AGridPiece* rightBottom = getGridPieceAt(selectedX + 1, selectedY - 1);
				//--- is there a piece on top?
				if (hasPieceOnTop(rightBottom)) {
					//--- Is it our own?
					if (getCheckerPieceOnTop(rightBottom)->getPlayer() != player) {
						//--- Work out jump over position
						int JumpOverX = selectedX + 2;
						int JumpoverY = selectedY - 2;

						//--- Make sure our y is not less than 0 (off the board)
						if (JumpoverY >= 0) {

							AGridPiece* JumpOverMove = getGridPieceAt(JumpOverX, JumpoverY);

							//--- Is there a piece there?
							if (!hasPieceOnTop(JumpOverMove)) {
								JumpOverMove->setTextureHighlight(true);
								possibleMoveGridPieces.push_back(JumpOverMove);
							}
						}
					}
				} else {
					//--- If no piece on top just normally highlight
					rightBottom->setTextureHighlight(true);
					possibleMoveGridPieces.push_back(rightBottom);
				}
			}
			if (!(selectedY == (GRID_SIZE - 1))) {
				//--- This is the TOP highlight
				AGridPiece* rightTop = getGridPieceAt(selectedX + 1, selectedY + 1);
				if (hasPieceOnTop(rightTop)) {
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Test1!"));
					if (getCheckerPieceOnTop(rightTop)->getPlayer() != player) {
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Test2!"));
						//--- Work out jump over position
						int JumpOverX = selectedX + 2;
						int JumpoverY = selectedY + 2;

						//--- Make sure our Y is not off the top of the board
						if (JumpoverY <= (GRID_SIZE - 1)) {
							GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Test3!"));

							AGridPiece* JumpOverMove = getGridPieceAt(JumpOverX, JumpoverY);

							//--- Is there a piece there?
							if (!hasPieceOnTop(JumpOverMove)) {
								GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Test4!"));
								JumpOverMove->setTextureHighlight(true);
								possibleMoveGridPieces.push_back(JumpOverMove);
							}
						}
					}
				} else {
					//--- If no piece on top just normally highlight
					rightTop->setTextureHighlight(true);
					possibleMoveGridPieces.push_back(rightTop);
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

bool ACheckerboardManager::vectorContains(std::vector<AGridPiece*> vectorToSearch, AGridPiece* gridPiece) {
	bool found = false;
	for (AGridPiece* gridPieceInLoop : vectorToSearch) {
		if (gridPieceInLoop == gridPiece)
			found = true;
	}

	return found;
}