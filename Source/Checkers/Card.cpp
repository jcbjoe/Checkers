// Fill out your copyright notice in the Description page of Project Settings.

#include "Card.h"


// Sets default values
ACard::ACard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> gridMesh(TEXT("StaticMesh'/Game/Models/Card/Low_Poly_Card.Low_Poly_Card'"));
	CardMesh_ = CreateDefaultSubobject < UStaticMeshComponent>(TEXT("BasePieceMesh"));

	CardMesh_->SetStaticMesh(gridMesh.Object);

	RootComponent = CardMesh_;

}

// Called when the game starts or when spawned
void ACard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACard::SelectCard() {
	int card = rand() % 100;
	int effect = rand() % 100;

	if ((card >= 0) && (card <= 75)) {
		//Good Effect
		if ((effect >= 0) && (effect <= 9)) {
			//Get a King
		}
		if ((effect >= 10) && (effect <= 79)) {
			//Extra Move
		}
		if ((effect >= 80) && (effect <= 99)) {
			//King for a Turn
		}
	}
	else if ((card >= 76) && (card <= 100)) {
		//Bad Effect
		if ((effect >= 0) && (effect <= 9)) {
			//Give Opponent King
		}
		if ((effect >= 10) && (effect <= 89)) {
			//Miss Next Turn
		}
		if ((effect >= 90) && (effect <= 99)) {
			//Lose Random Piece
		}
	}
}