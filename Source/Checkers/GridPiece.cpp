// Fill out your copyright notice in the Description page of Project Settings.

#include "GridPiece.h"


// Sets default values
AGridPiece::AGridPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> gridMesh(TEXT("StaticMesh'/Game/Models/mdl_GridPiece.mdl_GridPiece'"));
	gridPiece_ = CreateDefaultSubobject < UStaticMeshComponent>(TEXT("GridMesh"));

	gridPiece_->SetStaticMesh(gridMesh.Object);

	RootComponent = gridPiece_;

	initMaterials();

	initEvents();

}

void AGridPiece::initMaterials() {
	ConstructorHelpers::FObjectFinder<UMaterial> brownFinder(TEXT("Material'/Game/Materials/NormalBrown.NormalBrown'"));
	brown_ = brownFinder.Object;

	ConstructorHelpers::FObjectFinder<UMaterial> lightBrownFinder(TEXT("Material'/Game/Materials/NormalLightBrown.NormalLightBrown'"));
	lightBrown_ = lightBrownFinder.Object;

	ConstructorHelpers::FObjectFinder<UMaterial> brownFinderHighlight(TEXT("Material'/Game/Materials/NormalBrown.NormalBrown'"));
	brownHighlight_ = brownFinderHighlight.Object;

	ConstructorHelpers::FObjectFinder<UMaterial> lightBrownFinderHighlight(TEXT("Material'/Game/Materials/NormalLightBrown.NormalLightBrown'"));
	lightBrownHighlight_ = lightBrownFinderHighlight.Object;

}

void AGridPiece::initEvents() {
	gridPiece_->OnBeginCursorOver.AddDynamic(this, &AGridPiece::CustomOnBeginMouseOver);
	gridPiece_->OnEndCursorOver.AddDynamic(this, &AGridPiece::CustomOnEndMouseOver);
}

// Called when the game starts or when spawned
void AGridPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridPiece::setTextureHighlight(bool highlight)
{
	if (highlight) {
		if (currentMaterial == 0) {
			setTexture(2);
		}
		if (currentMaterial == 0) {
			setTexture(3);
		}
	} else {
		if (currentMaterial == 2) {
			setTexture(0);
		}
		if (currentMaterial == 3) {
			setTexture(1);
		}
	}

}

void AGridPiece::CustomOnBeginMouseOver(UPrimitiveComponent* TouchedComponent) {


}

void AGridPiece::CustomOnEndMouseOver(UPrimitiveComponent* TouchedComponent) {
}

void AGridPiece::setTexture(int colour) {
	switch (colour) {
		case 0: 
			gridPiece_->SetMaterial(0, brown_);
			currentMaterial = 0;
			break;
		
		case 1: 
			gridPiece_->SetMaterial(0, lightBrown_);
			currentMaterial = 1;
			break;
		
		case 2: 
			gridPiece_->SetMaterial(0, brownHighlight_);
			currentMaterial = 2;
			break;
		
		case 3: 
			gridPiece_->SetMaterial(0, brownHighlight_);
			currentMaterial = 3;
			break;
	}
}