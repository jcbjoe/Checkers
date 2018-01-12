// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Card.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/PointLightComponent.h"
#include "PlayerPawn.generated.h"

class AGameManager;

UCLASS()
class CHECKERS_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* card_;

	void setGameManager(AGameManager* man);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* OurCameraSpringArm;
	UPROPERTY(EditAnywhere)
	UCameraComponent* OurCamera;

	bool cameraMoving;
	bool spawnCard;
	bool spawnedCard;
	bool despawnCard;
	bool rotateCard;
	float cameraInput;
	float count;
	float x;
	float y;
	float z;
	float ry;

	void SelectCard();

	void initMaterials();

	//Good
	UMaterial* getAKingCard;
	UMaterial* extraMoveCard;
	UMaterial* oponentLoosesRandomPieceMat;
	//Bad
	UMaterial* GiveOpponentKingCard;
	UMaterial* missNextTurnCard;
	UMaterial* loseRandomPieceCard;

	int type;

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
	UPROPERTY(EditAnywhere)
	UPointLightComponent* MyLight;

private:
	AGameManager* GameManager;

	void endTurnDelayed();

	void startTimer();

	void executeCardAbility();

	bool extraMove;
};
