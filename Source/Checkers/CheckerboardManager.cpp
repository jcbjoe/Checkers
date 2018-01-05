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
	
}

// Called every frame
void ACheckerboardManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckerboardManager::createCheckerboard() {
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			AGridPiece* _gridPiece = GetWorld()->SpawnActor<AGridPiece>(FVector(i * 800, j * 800, 0.0), FRotator(0.0, 0.0, 0.0), FActorSpawnParameters());
		}
	}
}
