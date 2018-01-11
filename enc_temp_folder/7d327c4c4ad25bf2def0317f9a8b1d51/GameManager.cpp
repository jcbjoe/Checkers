// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "Blueprint/UserWidget.h"


// Sets default values
AGameManager::AGameManager(): lastSecond(0), playerTimerOn(false), playerTimerCurrentSeconds(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	
	checkerBoardManager = GetWorld()->SpawnActor<ACheckerboardManager>(FVector(0), FRotator(0), FActorSpawnParameters());

	checkerBoardManager->initManager(this);


	playersTurn = FMath::RandRange(0, 1);

	startTurn();
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (getPlayerController() != nullptr) {
		tickTimer();
	};
}

AMyPlayerController* AGameManager::getPlayerController() {
	return (AMyPlayerController*)(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

UMyUserWidget* AGameManager::getUI() {
	return getPlayerController()->getHudWidget();
}

void AGameManager::tickTimer() {
	int seconds = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	if (lastSecond <= seconds) {
		//--- 1 second

		seconds++;

		if (playerTimerOn) {
			if (playerTimerCurrentSeconds > 30) {
				playerTimerOn = false;
				endTurn();
			}
			if (playersTurn == 0)
				getUI()->setPlayer1Time(FString::FromInt(playerTimerCurrentSeconds));
			else
				getUI()->setPlayer2Time(FString::FromInt(playerTimerCurrentSeconds));
			playerTimerCurrentSeconds++;
			
		}

		//int hoursOut = seconds / 3600;
		int MinutesOut = seconds / 60;
		int secondsOut = seconds % 60;

		getPlayerController()->getHudWidget()->setGlobalTime(FString::FromInt(0) + FString(":") + FString::FromInt(MinutesOut) + FString(":") + FString::FromInt(secondsOut));
		lastSecond = seconds;
	}
}

void AGameManager::startTurn() {
	getUI()->setCurrentPlayer(playersTurn);
	playerTimerCurrentSeconds = 0;
	playerTimerOn = true;
}

void AGameManager::endTurn() {
	getUI()->despawnCard();
	if (playersTurn == 0) {
		playersTurn = 1;
		getUI()->setPlayer1Time(FString::FromInt(0));
	} else {
		playersTurn = 0;
		getUI()->setPlayer2Time(FString::FromInt(0));
	}
	startTurn();
}

int AGameManager::getCurrentPlayer() {
	return playersTurn;
}