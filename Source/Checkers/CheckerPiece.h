// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "DestructibleComponent.h"
#include "DestructibleMesh.h"
#include "DestructibleActor.h"
#include "MyAnimInstance.h"
#include "CheckerPiece.generated.h"

class ACheckerboardManager;

UCLASS()
class CHECKERS_API ACheckerPiece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckerPiece();

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* checkerPieceKingMesh_;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* sword_;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* spear_;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* checkerPiecePawnMesh_;

	UMyAnimInstance* pawnAnimInstance_;
	UMyAnimInstance* knightAnimInstance_;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void passVariables(int, int, int, ACheckerboardManager* cbm);

	UFUNCTION()
	void CustomOnBeginMouseOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void CustomOnEndMouseOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnClick(UPrimitiveComponent * ClickedComp, FKey ButtonPressed);

	int getPlayer();

	bool isKing();

	int getX();
	int getY();

	void setXY(int, int);
	
	void makeKing();

	void taken();

	void setAnimHit(bool);

private:

	UMaterial* player1Material_;
	UMaterial* player2Material_;

	UMaterial* player1MaterialKingBody_;
	UMaterial* player1MaterialKingExtra_;

	UMaterial* player2MaterialKingBody_;
	UMaterial* player2MaterialKingExtra_;

	UMaterial* player1SpearMaterial_;
	UMaterial* player2SpearMaterial_;

	UMaterial* player1SwordMaterial_;
	UMaterial* player2SwordMaterial_;

	int x;
	int y;
	int player;
	bool king;

	ACheckerboardManager* checkerBoardManager_;

	void initEvents();
	void initMaterials();

	UFUNCTION()
	void removeDebris(ADestructibleActor* mesh);
};
