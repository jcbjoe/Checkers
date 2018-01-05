// Fill out your copyright notice in the Description page of Project Settings.

#include "GridPiece.h"

#include "CheckerboardManager.h"


// Sets default values
AGridPiece::AGridPiece(): x(0), y(0), type(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> gridMesh(TEXT("StaticMesh'/Game/Models/mdl_GridPiece.mdl_GridPiece'"));
	gridPieceMesh_ = CreateDefaultSubobject < UStaticMeshComponent>(TEXT("GridMesh"));

	gridPieceMesh_->SetStaticMesh(gridMesh.Object);

	RootComponent = gridPieceMesh_;

	initMaterials();

	initEvents();

}

void AGridPiece::initMaterials() {
	ConstructorHelpers::FObjectFinder<UMaterial> brownFinder(TEXT("Material'/Game/Materials/NormalBrown.NormalBrown'"));
	brown_ = brownFinder.Object;

	ConstructorHelpers::FObjectFinder<UMaterial> lightBrownFinder(TEXT("Material'/Game/Materials/NormalLightBrown.NormalLightBrown'"));
	lightBrown_ = lightBrownFinder.Object;

	ConstructorHelpers::FObjectFinder<UMaterial> brownFinderHighlight(TEXT("Material'/Game/Materials/NormalBrownHighlight.NormalBrownHighlight'"));
	brownHighlight_ = brownFinderHighlight.Object;

	ConstructorHelpers::FObjectFinder<UMaterial> lightBrownFinderHighlight(TEXT("Material'/Game/Materials/NormalLightBrownHighlight.NormalLightBrownHighlight'"));
	lightBrownHighlight_ = lightBrownFinderHighlight.Object;

	ConstructorHelpers::FObjectFinder<UMaterial> selectedFinder(TEXT("Material'/Game/Materials/Selected.Selected'"));
	selected_ = selectedFinder.Object;

}

void AGridPiece::initEvents() {
	gridPieceMesh_->OnBeginCursorOver.AddDynamic(this, &AGridPiece::CustomOnBeginMouseOver);
	gridPieceMesh_->OnEndCursorOver.AddDynamic(this, &AGridPiece::CustomOnEndMouseOver);
	gridPieceMesh_->OnClicked.AddDynamic(this, &AGridPiece::OnClick);
}

void AGridPiece::passVariables(int passedX, int passedY, int texture, ACheckerboardManager* cbm) {
	x = passedX;
	y = passedY;
	type = texture;
	setTexture(texture);
	checkerBoardManager_ = cbm;
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
		if (currentMaterial == 1) {
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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("X:") + FString::FromInt(x));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Y:") + FString::FromInt(y));
	setTextureHighlight(true);
}

void AGridPiece::CustomOnEndMouseOver(UPrimitiveComponent* TouchedComponent) {
	setTextureHighlight(false);
}

void AGridPiece::setTexture(int colour) {
	switch (colour) {
		case 0: 
			gridPieceMesh_->SetMaterial(0, brown_);
			currentMaterial = 0;
			break;
		
		case 1: 
			gridPieceMesh_->SetMaterial(0, lightBrown_);
			currentMaterial = 1;
			break;
		
		case 2: 
			gridPieceMesh_->SetMaterial(0, brownHighlight_);
			currentMaterial = 2;
			break;
		
		case 3: 
			gridPieceMesh_->SetMaterial(0, lightBrownHighlight_);
			currentMaterial = 3;
			break;
		case 4:
			gridPieceMesh_->SetMaterial(0, selected_);
			currentMaterial = 4;
			break;
	}
}

void AGridPiece::OnClick(UPrimitiveComponent * ClickedComp, FKey ButtonPressed) {

	checkerBoardManager_->setSelected(x, y);

}

void AGridPiece::setSelected(bool selected) {
	if (selected) {
		setTexture(4);
	} else
		setTexture(type);
}

int AGridPiece::getX() {
	return x;
}
int AGridPiece::getY() {
	return y;
}