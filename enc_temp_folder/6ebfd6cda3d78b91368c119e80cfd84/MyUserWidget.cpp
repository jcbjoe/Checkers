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

void UMyUserWidget::setCurrentPlayer(FString time) {
	CurrentPlayer = time;
}

void UMyUserWidget::setAlertMessage(FString message, int displayTime) {

	AlertMessage = message;

	delayTime = displayTime;

	showAlertMessage = true;

}

void UMyUserWidget::chooseCard(FString message) {

	AlertMessage = message;

	showAlertMessage = true;

	hidden = true;

}

void UMyUserWidget::despawnCard() {
	playerPawn->DespawnCard();
}