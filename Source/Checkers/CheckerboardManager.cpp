// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckerboardManager.h"
#include "GameManager.h"

// Sets default values
ACheckerboardManager::ACheckerboardManager() : selectedX(0), selectedY(0), pieceMoving(false), proposedPieceToTake(nullptr), takingPiece(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	canBeMovedArray = {};

}

// Called when the game starts or when spawned
void ACheckerboardManager::BeginPlay()
{
	Super::BeginPlay();
	
	playerPawn = (APlayerPawn*)((AMyPlayerController*)(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetPawn());
}

void ACheckerboardManager::initManager(AGameManager* GM) {
	createCheckerboard();
	GameManager = GM;
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
			if (distance > 0.01) {
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
				if (!checkerPieceMoving->isKing()) {
					int player = checkerPieceMoving->getPlayer();
					//--- Moving Right
					if (player == 0) {
						if (checkerPieceMoving->getX() == 0) {
							checkerPieceMoving->makeKing();
						}
					}
					//--- Moving Left
					if (player == 1) {
						if (checkerPieceMoving->getX() == (GRID_SIZE - 1)) {
							checkerPieceMoving->makeKing();
						}
					}
				}
				if (takingPiece) {
					vector<vector<AGridPiece*>> possibleMovesForSelectedGrid = findPossibleMoves(pieceToMoveTo);
					if (isThereAPieceCanTake(possibleMovesForSelectedGrid)) {
						showPossibleMoves(pieceToMoveTo);
						selectedX = pieceToMoveTo->getX();
						selectedY = pieceToMoveTo->getY();
						pieceToMoveTo->setSelected(true);

						possibleMovesTaking = possibleMovesForSelectedGrid;
					} else {
						removePossibleMoves();

						GameManager->endTurn();

						takingPiece = false;
					}
				}
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
		if ((takingPiece && (possibleMovesContains(gridPieceArray[x][y], possibleMovesTaking)) || !takingPiece)) {
			//bool canMoved = canThisPieceBeMoved(gridPieceArray[x][y]); // Generates Array
			//bool MoveContains = possibleMovesContains(gridPieceArray[x][y], canBeMovedArray);
			//if(canMoved || MoveContains){
				//--- Get old selected grid piece and unselect it.
				AGridPiece* oldSelectedGridPiece = getGridPieceAt(selectedX, selectedY);
				//--- Grab new selected grid piece

				UE_LOG(LogTemp, Warning, TEXT("SelectingAt X: %d SelectingAt Y: %d"), x, y);

				AGridPiece* newSelected = getGridPieceAt(x, y);
				GameManager->getUI()->setAlertMessage(FString("X: ") + FString::FromInt(x) + FString("y:") + FString::FromInt(y), 5);
				if (hasPieceOnTop(newSelected)) {
					//--- Grab our new checker piece
					ACheckerPiece* checkerPiece = getCheckerPieceAt(x, y);

					if (checkerPiece->getPlayer() != GameManager->getCurrentPlayer()) {
						//Display Message saying not piece
						GameManager->getUI()->setAlertMessage(FString("This is not your piece!"), 5);
					}
					else {

						oldSelectedGridPiece->setSelected(false);

						//--- Change selected vars
						selectedX = x;
						selectedY = y;

						//--- Remove old possible moves
						removePossibleMoves();
						//--- If there is a checker piece on top of the grid piece we have selected, remember you can select a grid piece by clicking the checker pawn too
						newSelected->setSelected(true);
						//--- Grab side and if they are a king
						int player = checkerPiece->getPlayer();
						bool isKing = checkerPiece->isKing();
						//--- Show the possible moves the player can make
						showPossibleMoves(newSelected);
					}
				} else {
					//--- Check the previous selected piece has a piece on top
					if (hasPieceOnTop(oldSelectedGridPiece)) {
						//--- Get all possible moves for the previous piece
						vector<vector<AGridPiece*>> possibleMovesForSelectedGrid = findPossibleMoves(oldSelectedGridPiece);
						//--- Check if the previous pieces moves contained the newly selected grid piece
						if (possibleMovesContains(newSelected, possibleMovesForSelectedGrid)) {
							//--- Is there another piece we have to take before moving?
							if (isThereAPieceCanTake(possibleMovesForSelectedGrid)) {
								//--- Can we take this newly selected piece ^^ Before we were checking if it existed to just move NOT TAKE
								if (canTakePiece(newSelected, possibleMovesForSelectedGrid)) {
									//--- Right we CAN take a piece - We hand over to tick to check if once moved there is another piece we can take.
									oldSelectedGridPiece->setSelected(false);
									checkerPieceMoving = getCheckerPieceOnTop(oldSelectedGridPiece);
									pieceToMoveTo = newSelected;
									pieceMoving = true;

									//--- Grab the piece we are taking and remove it.
									ACheckerPiece* pieceToTake = getPieceTaking(newSelected, possibleMovesForSelectedGrid);
									takePiece(pieceToTake);

									//--- Get rid of highlighted moves (dont need anymore)
									removePossibleMoves();
									//--- lets move but dont end turn yet!
									takingPiece = true;
								} else {
									GameManager->getUI()->setAlertMessage(FString("There is a piece you can take, You must take it!"), 5);
								}
							//--- If we cannot take the piece we just move normally and end our turn
							} else {
								oldSelectedGridPiece->setSelected(false);
								checkerPieceMoving = getCheckerPieceOnTop(oldSelectedGridPiece);
								pieceToMoveTo = newSelected;
								pieceMoving = true;

								removePossibleMoves();

								GameManager->endTurn();

							}
						}
					}
				}
			//} else {
			//	GameManager->getUI()->setAlertMessage(FString("There is another piece that can be taken, You must take that by default!"), 5);
			//}
		} else {
			GameManager->getUI()->setAlertMessage(FString("You can only move the piece that has been moved!"), 5);
		}
	}
}

void ACheckerboardManager::showPossibleMoves(AGridPiece* gridPiece) {

	vector<vector<AGridPiece*>> possibleMovesGridPieces = findPossibleMoves(gridPiece);

	for (std::vector<AGridPiece*> gridPieceVector : possibleMovesGridPieces) {
		gridPieceVector[0]->setHighlighted(true);
	}
}

vector<vector<AGridPiece*>> ACheckerboardManager::findPossibleMoves(AGridPiece* gridPiece) {

	int player = getCheckerPieceOnTop(gridPiece)->getPlayer();
	bool isKing = getCheckerPieceOnTop(gridPiece)->isKing();

	vector<vector<AGridPiece*>> possibleMovesGrid;

	//--- Check which player is moving
	int selectedGridPieceX = gridPiece->getX();
	int selectedGridPieceY = gridPiece->getY();
	if (player == 0 || isKing) {
		//--- So we are on the Right side going LEFT! So we need to go right so x  -1
		//--- This is the BOTTOM highlight
		//--- Check that the selected piece is not on the bottom of the grid
		if (!(selectedGridPieceX == 0)) {
			if (!(((selectedGridPieceX - 1) < 0) || ((selectedGridPieceY - 1) < 0))) {
				AGridPiece* leftBottom = getGridPieceAt(selectedGridPieceX - 1, selectedGridPieceY - 1);
				//--- Check if we need to jump over or not
				if (hasPieceOnTop(leftBottom)) {
					//--- JUMP
					if (getCheckerPieceOnTop(leftBottom)->getPlayer() != player) {
						int JumpOverX = selectedGridPieceX - 2;
						int JumpoverY = selectedGridPieceY - 2;

						//--- Make sure our y is not less than 0 (off the board)
						if (JumpoverY >= 0 && JumpOverX >= 0) {

							AGridPiece* JumpOverMove = getGridPieceAt(JumpOverX, JumpoverY);

							//--- Is there a piece there?
							if (!hasPieceOnTop(JumpOverMove)) {
								possibleMovesGrid.push_back({ JumpOverMove, leftBottom });
							}
						}
					}
				} else {
					//--- If no piece on top just normally highlight
					possibleMovesGrid.push_back({ leftBottom, nullptr });
				}
			}
		}
		//--- This is the TOP highlight
		//--- Check the selected piece is not on the top of the grid, its -1 because of the loop that builds the grid starts at 0
		if (!(selectedGridPieceY == (GRID_SIZE - 1))) {
			if (!(((selectedGridPieceX - 1) < 0) || ((selectedGridPieceY + 1) > (GRID_SIZE - 1)))) {
				//--- Left  top Piece
				AGridPiece* leftTop = getGridPieceAt(selectedGridPieceX - 1, selectedGridPieceY + 1);
				//--- is there a piece on top?
				if (hasPieceOnTop(leftTop)) {
					//--- Is it our own?
					if (getCheckerPieceOnTop(leftTop)->getPlayer() != player) {

						//--- Work out jump over position
						int JumpOverX = selectedGridPieceX - 2;
						int JumpoverY = selectedGridPieceY + 2;

						//--- Make sure our Y is not off the top of the board
						if (JumpoverY <= (GRID_SIZE - 1) && JumpOverX >= 0) {

							AGridPiece* JumpOverMove = getGridPieceAt(JumpOverX, JumpoverY);

							//--- Is there a piece there?
							if (!hasPieceOnTop(JumpOverMove)) {
								possibleMovesGrid.push_back({ JumpOverMove, leftTop });
							}
						}
					}
				} else {
					//--- If no piece on top just normally highlight
					possibleMovesGrid.push_back({ leftTop, nullptr });
				}
			}
		}
	}
	if (player == 1 || isKing) {
		//--- WE are on the LEFT side going RIGHT
		if (!(selectedY == 0)) {
			if (!(((selectedGridPieceX + 1) > (GRID_SIZE - 1)) || ((selectedGridPieceY - 1) < 0))) {
				//--- This is the BOTTOM highlight
				AGridPiece* rightBottom = getGridPieceAt(selectedGridPieceX + 1, selectedGridPieceY - 1);
				//--- is there a piece on top?
				if (hasPieceOnTop(rightBottom)) {
					//--- Is it our own?
					if (getCheckerPieceOnTop(rightBottom)->getPlayer() != player) {
						//--- Work out jump over position
						int JumpOverX = selectedGridPieceX + 2;
						int JumpoverY = selectedGridPieceY - 2;

						//--- Make sure our y is not less than 0 (off the board)
						if (JumpoverY >= 0 && JumpOverX < (GRID_SIZE - 1)) {

							AGridPiece* JumpOverMove = getGridPieceAt(JumpOverX, JumpoverY);

							//--- Is there a piece there?
							if (!hasPieceOnTop(JumpOverMove)) {
								possibleMovesGrid.push_back({ JumpOverMove, rightBottom });
							}
						}
					}
				} else {
					//--- If no piece on top just normally highlight
					possibleMovesGrid.push_back({ rightBottom, nullptr });
				}
			}
		}
		if (!(selectedY == (GRID_SIZE - 1))) {
			if (!(((selectedGridPieceX + 1) > (GRID_SIZE - 1)) || ((selectedGridPieceY + 1) > (GRID_SIZE - 1)))) {
				//--- This is the TOP highlight
				AGridPiece* rightTop = getGridPieceAt(selectedGridPieceX + 1, selectedGridPieceY + 1);
				if (hasPieceOnTop(rightTop)) {
					if (getCheckerPieceOnTop(rightTop)->getPlayer() != player) {
						//--- Work out jump over position
						int JumpOverX = selectedGridPieceX + 2;
						int JumpoverY = selectedGridPieceY + 2;

						//--- Make sure our Y is not off the top of the board
						if (JumpoverY <= (GRID_SIZE - 1) && JumpOverX < (GRID_SIZE - 1)) {

							AGridPiece* JumpOverMove = getGridPieceAt(JumpOverX, JumpoverY);

							//--- Is there a piece there?
							if (!hasPieceOnTop(JumpOverMove)) {
								possibleMovesGrid.push_back({ JumpOverMove, rightTop });
							}
						}
					}
				} else {
					//--- If no piece on top just normally highlight
					possibleMovesGrid.push_back({ rightTop, nullptr });
				}
			}
		}
	}

	return possibleMovesGrid;
}

void ACheckerboardManager::removePossibleMoves() {

	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			gridPieceArray[x][y]->setHighlighted(false);
		}
	}
}

void ACheckerboardManager::createCheckerboard() {
	bool colourChanger = false;
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			//--- Spawn grid piece
			auto world = GetWorld();
			AGridPiece* gridPiece_ = GetWorld()->SpawnActor<AGridPiece>(AGridPiece::StaticClass(), FVector(i * 9.207275, j * 9.207275, 107.611404), FRotator(0.0, 0.0, 0.0), FActorSpawnParameters());
			int newX = GRID_SIZE - i - 1;
			if (colourChanger) 
				gridPiece_->passVariables(newX, j, 0, this);
			else
				gridPiece_->passVariables(newX, j, 1, this);
			gridPieceArray[newX][j] = gridPiece_;
			

			if ((i == 0 || i == 1 || i == 2 || i == (GRID_SIZE - 1) || i == (GRID_SIZE - 2) || i == (GRID_SIZE - 3)) && colourChanger) {
				//--- Spawn player pieces


				UE_LOG(LogTemp, Warning, TEXT("Given X: %d Given Y: %d"), newX, j);
				//UE_LOG(LogTemp, Warning, TEXT("Given X: ") + FString::FromInt(newX) + TEXT("Given Y: ") + FString::FromInt(y));
				ACheckerPiece* checkerPiece_;
				if (i == 0 || i == 1 || i == 2) {
					checkerPiece_ = GetWorld()->SpawnActor<ACheckerPiece>(ACheckerPiece::StaticClass(), FVector(i * 9.207275, j * 9.207275, 108.697784), FRotator(0, -90, 90), FActorSpawnParameters());
					checkerPieceArray[newX][j] = checkerPiece_;
					//--- Player 0
					checkerPiece_->passVariables(newX, j, 0, this);
				} else {
					checkerPiece_ = GetWorld()->SpawnActor<ACheckerPiece>(ACheckerPiece::StaticClass(), FVector(i * 9.207275, j * 9.207275, 108.697784), FRotator(0, 90, 90), FActorSpawnParameters());
					checkerPieceArray[newX][j] = checkerPiece_;
					//--- Player 1
					checkerPiece_->passVariables(newX, j, 1, this);
				}
				UE_LOG(LogTemp, Warning, TEXT("Actual X: %d Actual Y: %d"), checkerPiece_->getX(), checkerPiece_->getY());
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
	if (x > GRID_SIZE-1 || x < 0) {
		int breakPoint = 0;
		x = 0;
	}
	if (y > GRID_SIZE - 1 || y < 0) {
		int breakPoint = 0;
		y = 0;
	}
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

bool ACheckerboardManager::possibleMovesContains(AGridPiece* gridPiece, vector<vector<AGridPiece*>> possibleMoveGridPieces) {
	bool found = false;

	for (std::vector<AGridPiece*> gridPieceVector : possibleMoveGridPieces) {
		if (gridPieceVector[0] == gridPiece) {
			found = true;
		}
	}

	return found;
}

bool ACheckerboardManager::canTakePiece(AGridPiece* gridPiece, vector<vector<AGridPiece*>> possibleMovesGrid) {
	bool canTake = false;
	for (vector<AGridPiece*> gridPieceVector : possibleMovesGrid) {
		if (gridPieceVector[0] == gridPiece) {
			if (gridPieceVector[1] != nullptr) {
				canTake = true;
			}
		}
	}

	return canTake;
}

bool ACheckerboardManager::isThereAPieceCanTake(vector<vector<AGridPiece*>> possibleMovesGrid) {
	bool isThereAPieceCanTake = false;
	for (vector<AGridPiece*> gridPieceVector : possibleMovesGrid) {
		if (gridPieceVector[1] != nullptr) {
			isThereAPieceCanTake = true;
		}
	}

	return isThereAPieceCanTake;
}

ACheckerPiece* ACheckerboardManager::getPieceTaking(AGridPiece* gridPiece, vector<vector<AGridPiece*>> possibleMovesGrid) {
	ACheckerPiece* pieceInMiddle = nullptr;
	for (vector<AGridPiece*> gridPieceVector : possibleMovesGrid) {
		if (gridPieceVector[0] == gridPiece) {
			pieceInMiddle = getCheckerPieceOnTop(gridPieceVector[1]);
		}
	}

	
	return pieceInMiddle;
}

void ACheckerboardManager::takePiece(ACheckerPiece* checkerPiece) {
	int x = checkerPiece->getX();
	int y = checkerPiece->getY();
	checkerPieceArray[x][y] = nullptr;
	checkerPiece->taken();
	//checkerPiece->Destroy();
	GameManager->getUI()->chooseCard(FString("Do you want this card?"));
	playerPawn->SpawnCard();
}


bool ACheckerboardManager::canThisPieceBeMoved(AGridPiece* gridPiece) {

	int player = GameManager->getCurrentPlayer();

	bool returnVar = true;

	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			if (getCheckerPieceOnTop(gridPieceArray[x][y]) != nullptr) {
				AGridPiece * gridPieceChoosen = gridPieceArray[x][y];
				if (getCheckerPieceOnTop(gridPieceChoosen)->getPlayer() == player) {
					vector<vector<AGridPiece*>> possibleMovesForSelectedGrid = findPossibleMoves(gridPieceChoosen);
					bool canTake = isThereAPieceCanTake(possibleMovesForSelectedGrid);
					if (canTake && !(gridPieceChoosen == gridPiece)) {
						returnVar = false;
					}
				}
			}
		}
	}
	if (getCheckerPieceOnTop(gridPiece)) {
		canBeMovedArray = findPossibleMoves(gridPiece);
	}

	return returnVar;

}

ACheckerPiece* ACheckerboardManager::randomPiece() {
	vector<ACheckerPiece*> pieces;
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			if (hasPieceOnTop(gridPieceArray[x][y])) {
				ACheckerPiece* piece = checkerPieceArray[x][y];
				if (piece->getPlayer() == GameManager->getCurrentPlayer()) {
					pieces.push_back(piece);
				}
			}
		}
	}

	int Random = rand() % pieces.size();
	return pieces.at(Random);
}