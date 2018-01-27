// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckerPiece.h"

#include "CheckerboardManager.h"

// Sets default values
ACheckerPiece::ACheckerPiece(): x(0),y(0),player(0),king(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//
	//	Pawn Setup
	//

	ConstructorHelpers::FObjectFinder<UStaticMesh> spearMesh(TEXT("StaticMesh'/Game/Models/Pawns/Spear/spear_basemesh.spear_basemesh'"));
	spear_ = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("Spear"));
	spear_->SetStaticMesh(spearMesh.Object);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> pawnMesh(TEXT("SkeletalMesh'/Game/Models/Pawns/Normal/Animation/Pawn_Animation.Pawn_Animation'"));

	checkerPiecePawnMesh_ = CreateDefaultSubobject <USkeletalMeshComponent>(TEXT("Pawn"));

	checkerPiecePawnMesh_->SetSkeletalMesh(pawnMesh.Object);

	ConstructorHelpers::FObjectFinder<UAnimBlueprintGeneratedClass> PawnAnimBP(TEXT("/Game/Models/Pawns/Normal/Animation/PawnAnimBlueprint.PawnAnimBlueprint_c"));

	checkerPiecePawnMesh_->AnimClass = PawnAnimBP.Object;

	checkerPiecePawnMesh_->SetWorldScale3D(FVector(0.0365, 0.0365, 0.0365));

	RootComponent = checkerPiecePawnMesh_;


	// 
	//	Knight Setup
	//
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> swordrMesh(TEXT("StaticMesh'/Game/Models/Pawns/Sword/sword_gamemesh.sword_gamemesh'"));
	sword_ = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("Sword"));
	sword_->SetStaticMesh(swordrMesh.Object);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> kingMesh(TEXT("SkeletalMesh'/Game/Models/Pawns/King/Animation/Knight_Anim.Knight_Anim'"));

	checkerPieceKingMesh_ = CreateDefaultSubobject <USkeletalMeshComponent>(TEXT("Knight"));

	checkerPieceKingMesh_->SetSkeletalMesh(kingMesh.Object);

	ConstructorHelpers::FObjectFinder<UAnimBlueprintGeneratedClass> KnightAnimBP(TEXT("/Game/Models/Pawns/King/Animation/KnightBlueprint.KnightBlueprint_c"));

	checkerPieceKingMesh_->AnimClass = KnightAnimBP.Object;

	checkerPieceKingMesh_->SetVisibility(false);
	sword_->SetVisibility(false);
	
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

	ConstructorHelpers::FObjectFinder<UMaterial> player1MatSword(TEXT("Material'/Game/Models/Pawns/Sword/SwordB.SwordB'"));
	player1SwordMaterial_ = player1MatSword.Object;

	ConstructorHelpers::FObjectFinder<UMaterial> player2MatSword(TEXT("Material'/Game/Models/Pawns/Sword/SwordW.SwordW'"));
	player2SwordMaterial_ = player2MatSword.Object;

}

void ACheckerPiece::initEvents() {
	checkerPiecePawnMesh_->OnBeginCursorOver.AddDynamic(this, &ACheckerPiece::CustomOnBeginMouseOver);
	checkerPiecePawnMesh_->OnEndCursorOver.AddDynamic(this, &ACheckerPiece::CustomOnEndMouseOver);
	checkerPiecePawnMesh_->OnClicked.AddDynamic(this, &ACheckerPiece::OnClick);
}

// Called when the game starts or when spawned
void ACheckerPiece::BeginPlay()
{
	Super::BeginPlay();
	checkerPieceKingMesh_->SetRelativeRotation(FRotator(0, 0, 0));
	checkerPieceKingMesh_->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	sword_->SetRelativeLocation(FVector(28.76734, 3.564586, -90.630302));
	sword_->SetRelativeRotation(FRotator(-1.53152, 50.711842, -85.49662));
	sword_->SetWorldScale3D(FVector(0.6,0.6,0.6));
	sword_->AttachToComponent(checkerPieceKingMesh_, FAttachmentTransformRules::KeepRelativeTransform, "Base-HumanRPalm");

	spear_->SetRelativeLocation(FVector(29.785242, 13.054083, 62.272045));
	spear_->SetRelativeRotation(FRotator(-7.237617, 54.944157, -88.953293));
	spear_->SetWorldScale3D(FVector(0.28, 0.28, 0.28));
	spear_->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, "Base-HumanRPalm");

	pawnAnimInstance_ = Cast<UMyAnimInstance>(checkerPiecePawnMesh_->GetAnimInstance());
	knightAnimInstance_ = Cast<UMyAnimInstance>(checkerPieceKingMesh_->GetAnimInstance());
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
		checkerPiecePawnMesh_->SetMaterial(0, player1Material_);

		checkerPieceKingMesh_->SetMaterial(2, player1MaterialKingBody_);
		checkerPieceKingMesh_->SetMaterial(0, player1MaterialKingExtra_);
		checkerPieceKingMesh_->SetMaterial(1, player1MaterialKingExtra_);
		spear_->SetMaterial(0, player1SpearMaterial_);
		sword_->SetMaterial(0, player1SwordMaterial_);

	} else {
		checkerPiecePawnMesh_->SetMaterial(0, player2Material_);

		checkerPieceKingMesh_->SetMaterial(2, player2MaterialKingBody_);
		checkerPieceKingMesh_->SetMaterial(0, player2MaterialKingExtra_);
		checkerPieceKingMesh_->SetMaterial(1, player2MaterialKingExtra_);
		spear_->SetMaterial(0, player2SpearMaterial_);
		sword_->SetMaterial(0, player2SwordMaterial_);
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
	checkerPiecePawnMesh_->SetVisibility(false);
	spear_->SetVisibility(false);
	checkerPieceKingMesh_->SetVisibility(true);
	sword_->SetVisibility(true);
}

void ACheckerPiece::taken() {
	UDestructibleMesh* DestructibleMesh;
	if (isKing()) {
		DestructibleMesh = Cast<UDestructibleMesh>(StaticLoadObject(UDestructibleMesh::StaticClass(), NULL, TEXT("/Game/Models/Pawns/King/king_gamemesh_DM.king_gamemesh_DM")));
	}
	else {
		DestructibleMesh = Cast<UDestructibleMesh>(StaticLoadObject(UDestructibleMesh::StaticClass(), NULL, TEXT("/Game/Models/Pawns/Normal/together_DM.together_DM")));
	}
	ADestructibleActor* DestructibleActor;
	FVector loc = FVector(this->GetActorTransform().GetTranslation().X, this->GetActorTransform().GetTranslation().Y, this->GetActorTransform().GetTranslation().Z);
	if (player == 0) {
		DestructibleActor = GetWorld()->SpawnActor<ADestructibleActor>(ADestructibleActor::StaticClass(), loc, FRotator(0, -90, 0));
	}
	else {
		DestructibleActor = GetWorld()->SpawnActor<ADestructibleActor>(ADestructibleActor::StaticClass(), loc, FRotator(0, 90, 0));
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

	DestructibleActor->SetActorScale3D(FVector(0.01436, 0.01436, 0.01436));
	DestructibleActor->GetDestructibleComponent()->SetDestructibleMesh(DestructibleMesh);

	checkerPiecePawnMesh_->SetVisibility(false);
	spear_->SetVisibility(false);

	FTimerHandle UnusedHandle;
	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("removeDebris"), DestructibleActor);

	//GetWorldTimerManager().SetTimer(UnusedHandle, TimerDel, 5, false);
}

void ACheckerPiece::removeDebris(ADestructibleActor* mesh) {
	mesh->Destroy();
}

void ACheckerPiece::setAnimHit(bool hit) {
	if (isKing()) {
		knightAnimInstance_->setHit(hit);
	} else {
		pawnAnimInstance_->setHit(hit);
	}
}
