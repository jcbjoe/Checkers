// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "GridPiece.generated.h"


class ACheckerboardManager;

UCLASS()
class CHECKERS_API AGridPiece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridPiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* gridPiece_;
	
	void setTexture(int tex);
	void setTextureHighlight(bool highlight);

	UFUNCTION()
	void CustomOnBeginMouseOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void CustomOnEndMouseOver(UPrimitiveComponent* TouchedComponent);

	void passVariables(int x, int y, int texture, ACheckerboardManager* cbm);
	
private:
	UMaterial* brown_;
	UMaterial* lightBrown_;
	UMaterial* brownHighlight_;
	UMaterial* lightBrownHighlight_;

	int currentMaterial;

	void initEvents();

	void initMaterials();

	int x;
	int y;

	ACheckerboardManager* checkerBoardManager_;
	
};
