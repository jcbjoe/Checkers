// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckerPiece.h"

#include "CheckerboardManager.h"

// Sets default values
ACheckerPiece::ACheckerPiece(): x(0),y(0),player(0),king(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> gridMesh(TEXT("StaticMesh'/Game/Models/Pawns/Normal/pawn_gamemesh.pawn_gamemesh'"));
	checkerPieceMesh_ = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("BasePieceMesh"));
	checkerPieceMesh_->SetStaticMesh(gridMesh.Object);

	ConstructorHelpers::FObjectFinder<UStaticMesh> kingGridMesh(TEXT("StaticMesh'/Game/Models/Pawns/King/king_gamemesh.king_gamemesh'"));
	checkerPieceKingMesh_ = CreateDefaultSubobject < UStaticMeshComponent>(TEXT("KingMesh"));
	checkerPieceKingMesh_->SetStaticMesh(kingGridMesh.Object);

	checkerPieceKingMesh_->SetVisibility(false);
	checkerPieceKingMesh_->SetMobility(EComponentMobility::Movable);

	//ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMesh(TEXT("SkeletalMesh'/Game/Models/Pawns/Normal/anim/test123.test123'"));

	//USkeletalMeshComponent* meshComp = CreateDefaultSubobject <USkeletalMeshComponent>(TEXT("Skeletal"));

	//meshComp->SetSkeletalMesh(skeletalMesh.Object);

	//// load the animation blueprint
	//const ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimObj(TEXT("AnimBlueprint'/Game/Models/Pawns/Normal/anim/NewAnimBlueprint.NewAnimBlueprint'"));


	//meshComp->SetAnimInstanceClass(AnimObj.Object->GeneratedClass);

	//meshComp->SetWorldScale3D(FVector(0.0125, 0.0125, 0.0125));

	checkerPieceKingMesh_->SetWorldScale3D(FVector(1.75, 1.75, 1.75));
	checkerPieceMesh_->SetWorldScale3D(FVector(1.75, 1.75, 1.75));
	
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
	checkerPieceKingMesh_->SetRelativeRotation(FRotator(0, 0, 0));
	checkerPieceKingMesh_->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
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
}

void ACheckerPiece::taken() {
	UDestructibleMesh* DestructibleMesh;
	if (isKing()) {
		DestructibleMesh = Cast<UDestructibleMesh>(StaticLoadObject(UDestructibleMesh::StaticClass(), NULL, TEXT("/Game/Models/Pawns/King/king_gamemesh_DM.king_gamemesh_DM")));
	}
	else {
		DestructibleMesh = Cast<UDestructibleMesh>(StaticLoadObject(UDestructibleMesh::StaticClass(), NULL, TEXT("/Game/Models/Pawns/Normal/pawn_gamemesh_DM.pawn_gamemesh_DM")));
	}

	ADestructibleActor* DestructibleActor = GetWorld()->SpawnActor<ADestructibleActor>(ADestructibleActor::StaticClass(), FVector(0,0,0), FRotator(0, -90, 90));

	if (player == 1) {
		if (isKing()) {
			DestructibleActor->GetDestructibleComponent()->SetMaterial(2, player1MaterialKingBody_);
			DestructibleActor->GetDestructibleComponent()->SetMaterial(0, player1MaterialKingExtra_);
			DestructibleActor->GetDestructibleComponent()->SetMaterial(1, player1MaterialKingExtra_);
		} else {
			DestructibleActor->GetDestructibleComponent()->SetMaterial(0, player1Material_);
		}
	} else {
		if (isKing()) {
			DestructibleActor->GetDestructibleComponent()->SetMaterial(2, player2MaterialKingBody_);
			DestructibleActor->GetDestructibleComponent()->SetMaterial(0, player2MaterialKingExtra_);
			DestructibleActor->GetDestructibleComponent()->SetMaterial(1, player2MaterialKingExtra_);
		} else {
			DestructibleActor->GetDestructibleComponent()->SetMaterial(0, player2Material_);
		}
	}

	DestructibleActor->SetActorScale3D(FVector(1.75, 1.75, 1.75));
	DestructibleActor->SetActorTransform(this->GetActorTransform());
	DestructibleActor->GetDestructibleComponent()->SetDestructibleMesh(DestructibleMesh);
	checkerPieceMesh_->SetVisibility(false);

	FTimerHandle UnusedHandle;
	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("removeDebris"), DestructibleActor);

	GetWorldTimerManager().SetTimer(UnusedHandle, TimerDel, 5, false);
}

void ACheckerPiece::removeDebris(ADestructibleActor* mesh) {
	mesh->Destroy();
}