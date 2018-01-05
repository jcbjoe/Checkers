// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridPiece.h"
#include "CheckerPiece.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include <EngineGlobals.h>
#include <vector>
#include "CheckerboardManager.generated.h"


UCLASS()
class CHECKERS_API ACheckerboardManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckerboardManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AGridPiece* getGridPieceAt(int x, int y);
	ACheckerPiece* getCheckerPieceAt(int x, int y);

	void setSelected(int, int);


private: 
	static const int GRID_SIZE = 8;

	AGridPiece* gridPieceArray[GRID_SIZE][GRID_SIZE];
	ACheckerPiece* checkerPieceArray[GRID_SIZE][GRID_SIZE];

	void createCheckerboard();

	int selectedX;
	int selectedY;
	
	void showPossibleMoves(int player, bool isKing);

	std::vector<AGridPiece*> possibleMoveGridPieces;

	void removePossibleMoves();

	bool hasPieceOnTop(AGridPiece* gridPiece);

	ACheckerPiece* getCheckerPieceOnTop(AGridPiece* gridPiece);
};
