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

	OurCameraSpringArm->TargetArmLength = 90.f;

	OurCameraSpringArm->bEnableCameraLag = true;

	OurCameraSpringArm->CameraLagSpeed = 3.0f;

	OurCameraSpringArm->bDoCollisionTest = false;


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



	FRotator Rotation(0.0f, 0.0f, 0.0f);

	FVector startLocation(27.621824f, 36.829102f, 80.358833f);

	this->SetActorLocationAndRotation(startLocation, Rotation);
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

