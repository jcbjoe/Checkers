// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Card.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerPawn.generated.h"

UCLASS()
class CHECKERS_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* attachPoint_;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* OurCameraSpringArm;
	UPROPERTY(EditAnywhere)
	UCameraComponent* OurCamera;

	ACard* card;

	bool cameraMoving;
	bool spawnCard;
	bool spawnedCard;
	bool despawnCard;
	bool rotateCard;
	float cameraInput;
	float count;
	int x;
	int y;
	int z;
	int ry;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void RotateRight();
	void RotateLeft();
	void SpawnCard();
	void DespawnCard();
	void RotateCard();
};
