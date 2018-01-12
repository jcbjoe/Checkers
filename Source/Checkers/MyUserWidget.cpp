// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUserWidget.h"
#include "GameManager.h"


void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	playerPawn = (APlayerPawn*)((AMyPlayerController*)(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetPawn());
}

void UMyUserWidget::setPlayer1Time(FString time) {
	Player1Time = time;
}

void UMyUserWidget::setPlayer2Time(FString time) {
	Player2Time = time;
}

void UMyUserWidget::setGlobalTime(FString time) {
	GlobalTime = time;
}

void UMyUserWidget::setPlayer1Score(FString time) {
	Player1Score = time;
}
void UMyUserWidget::setPlayer2Score(FString time) {
	Player2Score = time;
}

void UMyUserWidget::setCurrentPlayer(int time) {
	CurrentPlayer = time;
}

void UMyUserWidget::setAlertMessage(FString message, int displayTime) {

	AlertMessage = message;

	delayTime = displayTime;

	showAlertMessage = true;

	FTimerHandle UnusedHandle;
	playerPawn->GetWorldTimerManager().SetTimer(UnusedHandle, this, &UMyUserWidget::turnOffAlert, delayTime, false);

}

void UMyUserWidget::turnOffAlert() {
	showAlertMessage = false;
}

void UMyUserWidget::spawnCardText() {

	hidden = true;

}

void UMyUserWidget::rotateCard() {
	playerPawn->RotateCard();

}

void UMyUserWidget::despawnCard() {
	hidden = false;
	playerPawn->DespawnCard();

}

void UMyUserWidget::setShowNotYourPiece(bool show) {
	showNotYourPiece = show;
}

void UMyUserWidget::showEnd(int player) {
	gameOver = true;
	if (player == 1)
		playerOneWins = true;
	if (player == 0)
		playerOneWins = false;
}