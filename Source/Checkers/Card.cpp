// Fill out your copyright notice in the Description page of Project Settings.

#include "Card.h"


// Sets default values
ACard::ACard() : attached(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> gridMesh(TEXT("StaticMesh'/Game/Models/Card_Low_Poly.Card_Low_Poly'"));
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

	if (GetActorLocation().Z < 2700) {
		FVector NewLocation = GetActorLocation();
		NewLocation.Z += 500 * DeltaTime;
		SetActorLocation(NewLocation);
	}
	else {
		if (!attached) {
			((AMyPlayerController*)(UGameplayStatics::GetPlayerController(GetWorld(), 0)))->attachCard(this);
		}
	}
}

