// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"


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

	OurCameraSpringArm->TargetArmLength = 4000.f;

	OurCameraSpringArm->bEnableCameraLag = true;

	OurCameraSpringArm->CameraLagSpeed = 3.0f;

	OurCameraSpringArm->bDoCollisionTest = false;

	ConstructorHelpers::FObjectFinder<UStaticMesh> gridMesh(TEXT("StaticMesh'/Game/Models/Card_Low_Poly.Card_Low_Poly'"));
	attachPoint_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AttachPoint"));
	attachPoint_->SetStaticMesh(gridMesh.Object);
	attachPoint_->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);

	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));

	OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);



	//Take control of the default Player

	AutoPossessPlayer = EAutoReceiveInput::Player0;



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

	FVector startLocation(1400.f, 1400.f, 50.f);

	this->SetActorLocationAndRotation(startLocation, Rotation);
	
	//attachPoint_->SetRelativeLocationAndRotation(FVector(120.f, -40.f, -53.f), FRotator(0.0f, 90.0f, 0.0f));
	attachPoint_->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 0.f), FRotator(0.0f, 90.0f, 0.0f));

}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (cameraMoving) {
		FRotator NewRotation = GetActorRotation();
		float moveSpeed = 0.01;
		if (count < 90) {
			NewRotation.Yaw += cameraInput;
			SetActorRotation(NewRotation);
			count++;
		}
		else {
			cameraMoving = false;
		}
	}

	if (spawnCard) {
		FVector newLocation = GetActorLocation();
		if(newLocation.X < 120)
			newLocation.X += 1 * DeltaTime;
		if (newLocation.Y > -40)
			newLocation.Y += 1 * DeltaTime;
		if (newLocation.Z > -53)
			newLocation.Z += 1 * DeltaTime;
		SetActorRelativeLocation(newLocation);
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
	spawnCard = true;
}