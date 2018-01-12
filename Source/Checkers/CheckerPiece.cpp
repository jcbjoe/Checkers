// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckerPiece.h"

#include "CheckerboardManager.h"

// Sets default values
ACheckerPiece::ACheckerPiece(): x(0),y(0),player(0),king(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> gridMesh(TEXT("StaticMesh'/Game/Models/Pawns/Normal/pawn_gamemesh.pawn_gamemesh'"));
	checkerPieceMesh_ = CreateDefaultSubobject < UStaticMeshComponent>(TEXT("BasePieceMesh"));
	checkerPieceMesh_->SetStaticMesh(gridMesh.Object);


	ConstructorHelpers::FObjectFinder<UDestructibleMesh> destructiveMesh(TEXT("DestructibleMesh'/Game/Models/Pawns/Normal/pawn_gamemesh_DM.pawn_gamemesh_DM'"));
	destructableMesh = destructiveMesh.Object;
	destructive = CreateDefaultSubobject <UDestructibleComponent>(TEXT("DestructiveMesh"));


	ConstructorHelpers::FObjectFinder<UStaticMesh> kingGridMesh(TEXT("StaticMesh'/Game/Models/Pawns/King/king_gamemesh.king_gamemesh'"));
	checkerPieceKingMesh_ = CreateDefaultSubobject < UStaticMeshComponent>(TEXT("KingMesh"));
	checkerPieceKingMesh_->SetStaticMesh(kingGridMesh.Object);

	checkerPieceKingMesh_->SetVisibility(false);
	checkerPieceKingMesh_->SetMobility(EComponentMobility::Movable);


	RootComponent = checkerPieceMesh_;

	initEvents();

	initMaterials();

}

void ACheckerPiece::initMaterials() {
	ConstructorHelpers::FObjectFinder<UMaterial> player1Mat(TEXT("Material'/Game/Models/Pawns/Normal/Materials/TexB.TexB'"));
	player1Material_ = player1Mat.Object;

	ConstructorHelpers::FObjectFinder<UMaterial> player1MatKingBody(TEXT("Material'/Game/Models/Pawns/King/Textures/TexBodyB.TexBodyB'"));
	player1MaterialKingBody_ = player1Mat.Object;

	ConstructorHelpers::FObjectFinder<UMaterial> player1MatKingExtra(TEXT("Material'/Game/Models/Pawns/King/Textures/TexOtherB.TexOtherB'"));
	player1MaterialKingExtra_ = player1Mat.Object;

	ConstructorHelpers::FObjectFinder<UMaterial> player2Mat(TEXT("Material'/Game/Models/Pawns/Normal/Materials/TexW.TexW'"));
	player2Material_ = player2Mat.Object;

	ConstructorHelpers::FObjectFinder<UMaterial> player2MatKingBody(TEXT("Material'/Game/Models/Pawns/King/Textures/TexBodyW.TexBodyW'"));
	player2MaterialKingBody_ = player2Mat.Object;

	ConstructorHelpers::FObjectFinder<UMaterial> player2MatKingExtra(TEXT("Material'/Game/Models/Pawns/King/Textures/TexOtherW.TexOtherW'"));
	player2MaterialKingExtra_ = player2Mat.Object;

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
	//checkerPieceKingMesh_->SetRelativeLocation(FVector(0, 0, 100));
	checkerPieceKingMesh_->SetRelativeRotation(FRotator(0, 0, 0));
	checkerPieceKingMesh_->AttachTo(RootComponent);
	destructive->AttachTo(RootComponent);
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
	if (player == 1) {
		checkerPieceMesh_->SetMaterial(0, player1Material_);

		checkerPieceKingMesh_->SetMaterial(2, player1MaterialKingBody_);
		checkerPieceKingMesh_->SetMaterial(0, player1MaterialKingExtra_);
		checkerPieceKingMesh_->SetMaterial(1, player1MaterialKingExtra_);

	} else {
		checkerPieceMesh_->SetMaterial(0, player2Material_);

		checkerPieceKingMesh_->SetMaterial(2, player2MaterialKingBody_);
		checkerPieceKingMesh_->SetMaterial(0, player2MaterialKingExtra_);
		checkerPieceKingMesh_->SetMaterial(1, player2MaterialKingExtra_);
	}
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

void ACheckerPiece::makeKing() {
	king = true;
	checkerPieceMesh_->SetVisibility(false);
	checkerPieceKingMesh_->SetVisibility(true);
	RootComponent = checkerPieceKingMesh_;
	destructive->SetDestructibleMesh(destructableMesh);
}

void ACheckerPiece::taken() {
	checkerPieceMesh_->SetVisibility(false);
	destructive->SetDestructibleMesh(destructableMesh);
}