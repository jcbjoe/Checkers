// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "GameManager.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//Create our components

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));

	OurCameraSpringArm->SetupAttachment(RootComponent);

	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(-45.0f, 90.0f, 0.0f));

	OurCameraSpringArm->TargetArmLength = 90.f;

	OurCameraSpringArm->bEnableCameraLag = true;

	OurCameraSpringArm->CameraLagSpeed = 3.0f;

	OurCameraSpringArm->bDoCollisionTest = false;


	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));

	OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);



	//Take control of the default Player

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	ConstructorHelpers::FObjectFinder<UStaticMesh> gridMesh(TEXT("StaticMesh'/Game/Models/Card/Low_Poly_Card.Low_Poly_Card'"));
	attachPoint_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AttachPoint"));
	attachPoint_->SetStaticMesh(gridMesh.Object);
	attachPoint_->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* MyController = GetWorld()->GetFirstPlayerController();

	card = (ACard*)((AMyPlayerController*)(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetPawn());

	MyController->bShowMouseCursor = true;

	MyController->bEnableClickEvents = true;

	MyController->bEnableMouseOverEvents = true;



	FRotator Rotation(0.0f, 0.0f, 0.0f);

	FVector startLocation(27.621824f, 36.829102f, 80.358833f);

	this->SetActorLocationAndRotation(startLocation, Rotation);
	
	attachPoint_->SetRelativeLocationAndRotation(FVector(50.f, -10.f, -200.f), FRotator(0.0f, 90.0f, 0.0f));
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
		FVector newLocation = FVector(50.0 + x, -10.0 + y, -200.0 + z);
		if (newLocation.X < 120) {
			newLocation.X += 1;
			x++;
		}
		if (newLocation.Y > -40) {
			newLocation.Y -= 1;
			y--;
		}
		if (newLocation.Z < -53) {
			newLocation.Z += 1;
			z++;
		}
		if ((newLocation.X == 120) && (newLocation.Y == -40) && (newLocation.Z == -53))
			spawnCard = false;
		attachPoint_->SetRelativeLocation(newLocation);
	}

	if (despawnCard) {
		FVector newLocation = FVector(120.0 + x, -40.0 + y, -53.0 + z);
		if (newLocation.X > 50) {
			newLocation.X -= 1;
			x--;
		}
		if (newLocation.Y < -10) {
			newLocation.Y += 1;
			y++;
		}
		if (newLocation.Z > -200) {
			newLocation.Z -= 1;
			z--;
		}
		if ((newLocation.X == 50) && (newLocation.Y == -10) && (newLocation.Z == -200)) {
			despawnCard = false;
			attachPoint_->SetRelativeRotation(FRotator(0.0, 90.0, 0.0));
		}
		attachPoint_->SetRelativeLocation(newLocation);
	}

	if (rotateCard) {
		FRotator newRotation = FRotator(0.0, 90.0 + ry, 0.0);
		if (newRotation.Yaw < 260) {
			newRotation.Yaw += 1;
			ry++;
		}
		if (newRotation.Yaw == 260)
			rotateCard = false;
		attachPoint_->SetRelativeRotation(newRotation);
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
	card->SelectCard();
	spawnCard = true;
	spawnedCard = true;
	x = 0;
	y = 0;
	z = 0;
}

void APlayerPawn::DespawnCard() {
	if (spawnedCard) {
		despawnCard = true;
		x = 0;
		y = 0;
		z = 0;
		spawnedCard = false;
	}
}

void APlayerPawn::RotateCard() {
	rotateCard = true;
	ry = 0;
}