// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUserWidget.h"


void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

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