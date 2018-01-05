// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
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
	UStaticMeshComponent* checkerPieceMesh_;

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
	
private:
	int x;
	int y;
	int player;
	bool king;

	ACheckerboardManager* checkerBoardManager_;

	void initEvents();

};
