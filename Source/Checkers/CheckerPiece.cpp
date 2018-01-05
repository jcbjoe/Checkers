// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckerPiece.h"


// Sets default values
ACheckerPiece::ACheckerPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACheckerPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckerPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

