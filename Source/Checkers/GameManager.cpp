// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "Blueprint/UserWidget.h"


// Sets default values
AGameManager::AGameManager() : lastSecond(0), playerTimerOn(false), playerTimerCurrentSeconds(0), paused(false), inCardMenu(false), player0MissTurn(false), player1MissTurn(false), globalPause(false), madeChoice(false)
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

	((APlayerPawn*)((AMyPlayerController*)(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetPawn()))->setGameManager(this);
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
	if (lastSecond <= seconds && !globalPause) {
		//--- 1 second

		seconds++;

		if (playerTimerOn && !paused) {
			if (playerTimerCurrentSeconds > 30 && (checkerBoardManager->piecesRemaining() != 1)) {
				playerTimerOn = false;
				getUI()->showRunOutOfTime();
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
	int piecesRemaining = checkerBoardManager->piecesRemaining();
	if (piecesRemaining > 0) {
		if (playersTurn == 0) {
			playersTurn = 1;
			getUI()->setPlayer1Time(FString::FromInt(0));
		}
		else {
			playersTurn = 0;
			getUI()->setPlayer2Time(FString::FromInt(0));
		}
		checkerBoardManager->removeSelection();
		startTurn();
	}
	else
		endGame();
}

int AGameManager::getCurrentPlayer() {
	return playersTurn;
}

int AGameManager::getOtherPlayer() {
	if (playersTurn == 0)
		return 1;
	else
		return 0;
}

void AGameManager::PauseTimer(bool pause) {
	paused = pause;
}

void AGameManager::setGlobalPause(bool pause) {
	globalPause = pause;
}

bool AGameManager::isInCardMenu() {

	return inCardMenu;

}

void AGameManager::setIsInCardMenu(bool val) {
	inCardMenu = val;
}

ACheckerboardManager* AGameManager::getCheckerboardManager() {
	return checkerBoardManager;
}

void AGameManager::setPlayer0MissTurn(bool miss) {
	player0MissTurn = miss;
}
void AGameManager::setPlayer1MissTurn(bool miss) {
	player1MissTurn = miss;
}

bool AGameManager::isPlayer0MissingTurn() {
	return player0MissTurn;
}

bool AGameManager::isPlayer1MissingTurn() {
	return player1MissTurn;
}

void AGameManager::endGame() {
	getUI()->showEnd(getCurrentPlayer());
}

void AGameManager::resetTimer() {
	playerTimerCurrentSeconds = 0;
}

bool AGameManager::hasMadeChoice() {
	return madeChoice;
}

void AGameManager::makeChoice(bool choice) {
	madeChoice = choice;
}