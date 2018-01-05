// Fill out your copyright notice in the Description page of Project Settings.

#include "GridPiece.h"


// Sets default values
AGridPiece::AGridPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> gridMesh(TEXT("StaticMesh'/Game/Models/mdl_GridPiece.mdl_GridPiece'"));
	_gridPiece = CreateDefaultSubobject < UStaticMeshComponent>(TEXT("GridMesh"));

	_gridPiece->SetStaticMesh(gridMesh.Object);

	RootComponent = _gridPiece;

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

