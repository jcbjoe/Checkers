// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckerPiece.h"

#include "CheckerboardManager.h"

// Sets default values
ACheckerPiece::ACheckerPiece(): x(0),y(0),player(0),king(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ConstructorHelpers::FObjectFinder<UStaticMesh> gridMesh(TEXT("StaticMesh'/Game/Models/Pawns/Normal/pawn_gamemesh.pawn_gamemesh'"));
	//checkerPieceMesh_ = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("BasePieceMesh"));
	//checkerPieceMesh_->SetStaticMesh(gridMesh.Object);

	ConstructorHelpers::FObjectFinder<UStaticMesh> kingGridMesh(TEXT("StaticMesh'/Game/Models/Pawns/King/king_gamemesh.king_gamemesh'"));
	checkerPieceKingMesh_ = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("KingMesh"));
	checkerPieceKingMesh_->SetStaticMesh(kingGridMesh.Object);

	checkerPieceKingMesh_->SetVisibility(false);
	checkerPieceKingMesh_->SetMobility(EComponentMobility::Movable);

	ConstructorHelpers::FObjectFinder<UStaticMesh> spearMesh(TEXT("StaticMesh'/Game/Models/Pawns/Spear/spear_basemesh.spear_basemesh'"));
	spear = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("Spear"));
	spear->SetStaticMesh(spearMesh.Object);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMesh(TEXT("SkeletalMesh'/Game/Models/Pawns/Normal/Animation/Pawn_Animation.Pawn_Animation'"));

	meshComp = CreateDefaultSubobject <USkeletalMeshComponent>(TEXT("Skeletal"));

	meshComp->SetSkeletalMesh(skeletalMesh.Object);

	//// load the animation blueprint
	ConstructorHelpers::FObjectFinder<UAnimBlueprintGeneratedClass> AnimObj(TEXT("/Game/Models/Pawns/Normal/Animation/PawnAnimBlueprint.PawnAnimBlueprint_c"));


	meshComp->AnimClass = AnimObj.Object;

	
	/*animInstance->setHit(true);*/

	meshComp->SetWorldScale3D(FVector(0.0365, 0.0365, 0.0365));

	checkerPieceKingMesh_->SetWorldScale3D(FVector(1.75, 1.75, 1.75));
	//checkerPieceMesh_->SetWorldScale3D(FVector(1.75, 1.75, 1.75));
	
	RootComponent = meshComp;

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

	ConstructorHelpers::FObjectFinder<UMaterial> player1MatSpear(TEXT("Material'/Game/Models/Pawns/Spear/SpearB.SpearB'"));
	player1SpearMaterial_ = player1MatSpear.Object;

	ConstructorHelpers::FObjectFinder<UMaterial> player2MatSpear(TEXT("Material'/Game/Models/Pawns/Spear/SpearW.SpearW'"));
	player2SpearMaterial_ = player2MatSpear.Object;

}

void ACheckerPiece::initEvents() {
	meshComp->OnBeginCursorOver.AddDynamic(this, &ACheckerPiece::CustomOnBeginMouseOver);
	meshComp->OnEndCursorOver.AddDynamic(this, &ACheckerPiece::CustomOnEndMouseOver);
	meshComp->OnClicked.AddDynamic(this, &ACheckerPiece::OnClick);
}

// Called when the game starts or when spawned
void ACheckerPiece::BeginPlay()
{
	Super::BeginPlay();
	checkerPieceKingMesh_->SetRelativeRotation(FRotator(0, 0, 0));
	checkerPieceKingMesh_->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	spear->SetRelativeLocation(FVector(23.893864, 15.582496, 64.85891));
	spear->SetRelativeRotation(FRotator(-6.938352, 54.000397, -86.734001));
	spear->SetWorldScale3D(FVector(0.268502, 0.268502, 0.268502));
	spear->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, "Base-HumanRPalm");
	animInstance = Cast<UMyAnimInstance>(meshComp->GetAnimInstance());
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
		meshComp->SetMaterial(0, player1Material_);

		checkerPieceKingMesh_->SetMaterial(2, player1MaterialKingBody_);
		checkerPieceKingMesh_->SetMaterial(0, player1MaterialKingExtra_);
		checkerPieceKingMesh_->SetMaterial(1, player1MaterialKingExtra_);
		spear->SetMaterial(0, player1SpearMaterial_);

	} else {
		meshComp->SetMaterial(0, player2Material_);

		checkerPieceKingMesh_->SetMaterial(2, player2MaterialKingBody_);
		checkerPieceKingMesh_->SetMaterial(0, player2MaterialKingExtra_);
		checkerPieceKingMesh_->SetMaterial(1, player2MaterialKingExtra_);
		spear->SetMaterial(0, player2SpearMaterial_);
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
	meshComp->SetVisibility(false);
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
	ADestructibleActor* DestructibleActor;
	FVector loc = FVector(this->GetActorTransform().GetTranslation().X, this->GetActorTransform().GetTranslation().Y, this->GetActorTransform().GetTranslation().Z);
	if (player == 0) {
		DestructibleActor = GetWorld()->SpawnActor<ADestructibleActor>(ADestructibleActor::StaticClass(), loc, FRotator(0, -90, 90));
	}
	else {
		DestructibleActor = GetWorld()->SpawnActor<ADestructibleActor>(ADestructibleActor::StaticClass(), loc, FRotator(0, 90, 90));
	}

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
	DestructibleActor->GetDestructibleComponent()->SetDestructibleMesh(DestructibleMesh);
	meshComp->SetVisibility(false);

	FTimerHandle UnusedHandle;
	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("removeDebris"), DestructibleActor);

	//eGetWorldTimerManager().SetTimer(UnusedHandle, TimerDel, 5, false);
}

void ACheckerPiece::removeDebris(ADestructibleActor* mesh) {
	mesh->Destroy();
}

void ACheckerPiece::setAnimHit(bool hit) {
	animInstance->setHit(hit);
}