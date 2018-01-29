// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "GameManager.h"
#include "CheckerPiece.h"


// Sets default values
APlayerPawn::APlayerPawn() : cameraMoving(false), spawnCard(false), spawnedCard(false), despawnCard(false), rotateCard(false), type(0), extraMove(false)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//Create our components

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));

	OurCameraSpringArm->SetupAttachment(RootComponent);

	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(-45.0f, 90.0f, 0.0f));

	OurCameraSpringArm->TargetArmLength = 120.f;

	OurCameraSpringArm->bEnableCameraLag = true;

	OurCameraSpringArm->CameraLagSpeed = 3.0f;

	OurCameraSpringArm->bDoCollisionTest = false;

	ConstructorHelpers::FObjectFinder<UStaticMesh> gridMesh(TEXT("StaticMesh'/Game/Models/Card/New/Card.Card'"));
	card_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AttachPoint"));
	card_->SetStaticMesh(gridMesh.Object);
	card_->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);

	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));

	OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);

	MyLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("MyLight"));

	//Take control of the default Player

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	initMaterials();
}

void APlayerPawn::initMaterials() {

	ConstructorHelpers::FObjectFinder<UMaterial> getAKingCardMat(TEXT("Material'/Game/Models/Card/New/Materials/Textures/getKingCardMat.getKingCardMat'"));
	getAKingCard = getAKingCardMat.Object;

	ConstructorHelpers::FObjectFinder<UMaterial> extraMoveCardMat(TEXT("Material'/Game/Models/Card/New/Materials/Textures/takeAnExtraTurnMat.takeAnExtraTurnMat'"));
	extraMoveCard = extraMoveCardMat.Object;

	ConstructorHelpers::FObjectFinder<UMaterial> enemyLoosesRandomPiece(TEXT("Material'/Game/Models/Card/New/Materials/Textures/oponentLoosesRandomPiece.oponentLoosesRandomPiece'"));
	oponentLoosesRandomPieceMat = enemyLoosesRandomPiece.Object;

	ConstructorHelpers::FObjectFinder<UMaterial> GiveOpponentKingCardMat(TEXT("Material'/Game/Models/Card/New/Materials/Textures/giveYourOponentKing.giveYourOponentKing'"));
	GiveOpponentKingCard = GiveOpponentKingCardMat.Object;

	ConstructorHelpers::FObjectFinder<UMaterial> missNextTurnCardMat(TEXT("Material'/Game/Models/Card/New/Materials/Textures/missYourNextTurn.missYourNextTurn'"));
	missNextTurnCard = missNextTurnCardMat.Object;

	ConstructorHelpers::FObjectFinder<UMaterial> loseRandomPieceCardMat(TEXT("Material'/Game/Models/Card/New/Materials/Textures/looseARandoMPieceMat.looseARandoMPieceMat'"));
	loseRandomPieceCard = loseRandomPieceCardMat.Object;


}


// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* MyController = GetWorld()->GetFirstPlayerController();

	MyController->bShowMouseCursor = true;

	MyController->bEnableClickEvents = true;

	MyController->bEnableMouseOverEvents = true;



	FRotator Rotation(0.0f, 45.0f, 0.0f);

	FVector startLocation(32, 32, 107.611404);

	this->SetActorLocationAndRotation(startLocation, Rotation);
	
	card_->SetRelativeLocationAndRotation(FVector(10.f, 0.f, -15.f), FRotator(0.0f, 90.0f, 0.0f));

	MyLight->SetRelativeLocationAndRotation(FVector(-1.824101, -65.448853, 75.227783), FRotator(0,0,45));
	MyLight->SetIntensity(0);
	MyLight->SetAttenuationRadius(102);
	MyLight->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (cameraMoving) {
		FRotator NewRotation = this->GetActorRotation();
		float moveSpeed = 0.01;
		if (count < 90) {
			NewRotation.Yaw += cameraInput;
			this->SetActorRotation(NewRotation);
			count++;
		}
		else {
			cameraMoving = false;
		}
	}

	if (spawnCard) {
		FVector newLocation = FVector(10.0 + x, 0.0 + y, -15.0 + z);
		if (newLocation.X < 15.0) {
			newLocation.X += 0.1;
			x += 0.1;
		}
		if (newLocation.Y > 0.0) {
			newLocation.Y -= 0.1;
			y -= 0.1;
		}
		if (newLocation.Z < -2.5) {
			newLocation.Z += 0.1;
			z += 0.1;
		}
		if ((newLocation.X >= 15.0) && (newLocation.Y <= 0.0) && (newLocation.Z >= -2.5)) {
			spawnCard = false;
		}
		card_->SetRelativeLocation(newLocation);
	}

	if (despawnCard) {
		FVector newLocation = FVector(15.0 + x, 0.0 + y, -2.5 + z);
		if (newLocation.X > 10.0) {
			newLocation.X -= 0.1;
			x -= 0.1;
		}
		if (newLocation.Y < 0.0) {
			newLocation.Y += 0.1;
			y += 0.1;
		}
		if (newLocation.Z > -15.0) {
			newLocation.Z -= 0.1;
			z -= 0.1;
		}
		if ((newLocation.X <= 10.0) && (newLocation.Y >= 0.0) && (newLocation.Z <= -15.0)) {
			despawnCard = false;
			card_->SetRelativeRotation(FRotator(0.0, 90.0, 0.0));
		}
		card_->SetRelativeLocation(newLocation);
	}

	if (rotateCard) {
		FRotator newRotation = FRotator(0.0, 90.0 + ry, 0.0);
		if (newRotation.Yaw < 270) {
			newRotation.Yaw += 1;
			ry++;
		}
		if (newRotation.Yaw == 270)
			rotateCard = false;
		card_->SetRelativeRotation(newRotation);
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("RotateRight", IE_Pressed, this, &APlayerPawn::RotateRight);
	InputComponent->BindAction("RotateLeft", IE_Pressed, this, &APlayerPawn::RotateLeft);
}

void APlayerPawn::RotateRight() {
	if (!cameraMoving) {
		cameraInput = -1;
		cameraMoving = true;
		count = 0;
	}
}

void APlayerPawn::RotateLeft() {
	if (!cameraMoving) {
		cameraInput = 1;
		cameraMoving = true;
		count = 0;
	}
}

void APlayerPawn::SpawnCard() {
	SelectCard();
	spawnCard = true;
	spawnedCard = true;
	x = 0;
	y = 0;
	z = 0;
	MyLight->SetIntensity(300);

}

void APlayerPawn::DespawnCard() {
	if (spawnedCard == true) {
		despawnCard = true;
		x = 0;
		y = 0;
		z = 0;
		spawnCard = false;
		MyLight->SetIntensity(0);
	}
}

void APlayerPawn::declineCard() {
	if (!(GameManager->hasMadeChoice())) {
		GameManager->makeChoice(true);
		DespawnCard();
		endTurnDelayed();
	}
}

void APlayerPawn::AcceptCard() {
	if (!(GameManager->hasMadeChoice())) {
		GameManager->makeChoice(true);
		rotateCard = true;
		ry = 0;
		startTimer();
	}
}

void APlayerPawn::SelectCard() {
	int card = rand() % 100;
	int effect = rand() % 100;

	if ((card >= 0) && (card <= 75)) {
		//Good Effect
		if ((effect >= 0) && (effect <= 9)) {
			//Get a King
			card_->SetMaterial(0, getAKingCard);
			type = 1;
		}
		if ((effect >= 10) && (effect <= 79)) {
			//Extra Move
			card_->SetMaterial(0, extraMoveCard);
			type = 2;
		}
		if ((effect >= 80) && (effect <= 99)) {
			//Remove a random enemys piece
			card_->SetMaterial(0, oponentLoosesRandomPieceMat);
			type = 3;
		}
	}
	else if ((card >= 76) && (card <= 100)) {
		//Bad Effect
		if ((effect >= 0) && (effect <= 9)) {
			//Give Opponent King
			card_->SetMaterial(0, GiveOpponentKingCard);
			type = 4;
		}
		if ((effect >= 10) && (effect <= 89)) {
			//Miss Next Turn
			card_->SetMaterial(0, missNextTurnCard);
			type = 5;
		}
		if ((effect >= 90) && (effect <= 99)) {
			//Lose Random Piece
			card_->SetMaterial(0, loseRandomPieceCard);
			type = 6;
		}
	}
}

void APlayerPawn::setGameManager(AGameManager* man) {
	GameManager = man;
}

void APlayerPawn::startTimer() {

	executeCardAbility();

	if (extraMove) {
		GameManager->PauseTimer(false);
		GameManager->setIsInCardMenu(false);
	} else {
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &APlayerPawn::endTurnDelayed, 5, false);
	}

}

void APlayerPawn::endTurnDelayed() {


	GameManager->PauseTimer(false);
	GameManager->setIsInCardMenu(false);
	GameManager->endTurn();
}

void APlayerPawn::executeCardAbility() {

	int currentPlayer = GameManager->getCurrentPlayer();
	int enemy = 0;
	int random;
	if (currentPlayer == 0)
		enemy = 1;

	ACheckerPiece* piece;
	vector<ACheckerPiece*> notKings;

	switch (type) {
	//Good
		//Get a King
		case 1:
			notKings = GameManager->getCheckerboardManager()->findNotKing(GameManager->getCurrentPlayer());
			random = rand() % notKings.size();
			notKings.at(random)->makeKing();
			break;
		//ExtraMove
		case 2:
			extraMove = true;
			GameManager->resetTimer();
			break;
		//Enemy looses random piece
		case 3:
			piece = GameManager->getCheckerboardManager()->randomPiece(enemy);
			GameManager->getCheckerboardManager()->takePieceRemote(piece);
			break;
	//Bad
		//Give oponent king
		case 4:
			notKings = GameManager->getCheckerboardManager()->findNotKing(GameManager->getOtherPlayer());
			random = rand() % notKings.size();
			notKings.at(random)->makeKing();
			break;
		//Miss next turn
		case 5:
			if (GameManager->getCurrentPlayer() == 0) {
				GameManager->setPlayer0MissTurn(true);
			} else {
				GameManager->setPlayer1MissTurn(true);
			}
			break;
		//Lose random piece
		case 6:
			piece = GameManager->getCheckerboardManager()->randomPiece(currentPlayer);
			GameManager->getCheckerboardManager()->takePieceRemote(piece);
			break;
	}
}

void APlayerPawn::setPaused(bool paused) {
	GameManager->setGlobalPause(paused);
}