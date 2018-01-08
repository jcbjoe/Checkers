// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckerPiece.h"

#include "CheckerboardManager.h"

// Sets default values
ACheckerPiece::ACheckerPiece(): x(0),y(0),player(0),king(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> gridMesh(TEXT("StaticMesh'/Game/Models/Piece.Piece'"));
	checkerPieceMesh_ = CreateDefaultSubobject < UStaticMeshComponent>(TEXT("GridMesh"));

	checkerPieceMesh_->SetStaticMesh(gridMesh.Object);

	RootComponent = checkerPieceMesh_;

	initEvents();

	initMaterials();

}

void ACheckerPiece::initMaterials() {
	ConstructorHelpers::FObjectFinder<UMaterial> player1Mat(TEXT("Material'/Game/Materials/player1.player1'"));
	player1Material_ = player1Mat.Object;

	ConstructorHelpers::FObjectFinder<UMaterial> player2Mat(TEXT("Material'/Game/Materials/player2.player2'"));
	player2Material_ = player2Mat.Object;

}

void ACheckerPiece::initEvents() {
	checkerPieceMesh_->OnBeginCursorOver.AddDynamic(this, &ACheckerPiece::CustomOnBeginMouseOver);
	checkerPieceMesh_->OnEndCursorOver.AddDynamic(this, &ACheckerPiece::CustomOnEndMouseOver);
	checkerPieceMesh_->OnClicked.AddDynamic(this, &ACheckerPiece::OnClick);
}

// Called when the game starts or when spawned
void ACheckerPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckerPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckerPiece::passVariables(int i, int j, int passedPlayer, ACheckerboardManager* cbm) {

	x = i;
	y = j;
	player = passedPlayer;
	checkerBoardManager_ = cbm;
	if (player == 1)
		checkerPieceMesh_->SetMaterial(0, player1Material_);
	else
		checkerPieceMesh_->SetMaterial(0, player2Material_);
}

void ACheckerPiece::CustomOnBeginMouseOver(UPrimitiveComponent* TouchedComponent) {
	AGridPiece* gridPiece = checkerBoardManager_->getGridPieceAt(x, y);
	if (gridPiece != nullptr) {
		gridPiece->setHighlighted(true);
	}
}

void ACheckerPiece::CustomOnEndMouseOver(UPrimitiveComponent* TouchedComponent) {
	checkerBoardManager_->getGridPieceAt(x, y)->setHighlighted(false);
}

void ACheckerPiece::OnClick(UPrimitiveComponent * ClickedComp, FKey ButtonPressed) {

	checkerBoardManager_->onClicked(x, y);

}

int ACheckerPiece::getPlayer() {
	return player;
}

bool ACheckerPiece::isKing() {
	return king;
}

int ACheckerPiece::getX() {
	return x;
}

int ACheckerPiece::getY() {
	return y;
}

void ACheckerPiece::setXY(int passedX, int passedY) {
	x = passedX;
	y = passedY;
}