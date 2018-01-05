// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckerboardManager.h"


// Sets default values
ACheckerboardManager::ACheckerboardManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACheckerboardManager::BeginPlay()
{
	Super::BeginPlay();

	createCheckerboard();

	if (GEngine){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
	}
	
}

// Called every frame
void ACheckerboardManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckerboardManager::createCheckerboard() {
	bool colourChanger = false;
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			AGridPiece* _gridPiece = GetWorld()->SpawnActor<AGridPiece>(FVector(i * 400, j * 400, 0.0), FRotator(0.0, 0.0, 0.0), FActorSpawnParameters());
			if (colourChanger)
				_gridPiece->setTexture(0);
			else
				_gridPiece->setTexture(1);
			colourChanger = !colourChanger;
		}
		colourChanger = !colourChanger;
	}
}
