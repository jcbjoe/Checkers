// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUserWidget.h"
#include "GameManager.h"


void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	hideHUD = false;
	doubleJumpShow = false;
	runOutOfTimeShow = false;
	playerPawn = (APlayerPawn*)((AMyPlayerController*)(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetPawn());
}

void UMyUserWidget::setPlayer1Time(FString time) {
	if (isHudAvaliable()) {
		Player1Time = time;
	}
}

void UMyUserWidget::setPlayer2Time(FString time) {
	if (isHudAvaliable()) {
		Player2Time = time;
	}
}

void UMyUserWidget::setGlobalTime(FString time) {
	if (isHudAvaliable()) {
		GlobalTime = time;
	}
}

void UMyUserWidget::setPlayer1Score(FString time) {
	if (isHudAvaliable()) {
		Player1Score = time;
	}
}
void UMyUserWidget::setPlayer2Score(FString time) {
	if (isHudAvaliable()) {
		Player2Score = time;
	}
}

void UMyUserWidget::setCurrentPlayer(int time) {
	if (isHudAvaliable()) {
		CurrentPlayer = time;
	}
}

void UMyUserWidget::setAlertMessage(FString message, int displayTime) {
	if (isHudAvaliable()) {
		AlertMessage = message;

		delayTime = displayTime;

		showAlertMessage = true;

		FTimerHandle UnusedHandle;
		playerPawn->GetWorldTimerManager().SetTimer(UnusedHandle, this, &UMyUserWidget::turnOffAlert, delayTime, false);
	}

}

void UMyUserWidget::turnOffAlert() {
	if (isHudAvaliable()) {
		showAlertMessage = false;
	}
}

void UMyUserWidget::spawnCardText() {
	if (isHudAvaliable()) {
		hidden = true;
	}

}

void UMyUserWidget::acceptCard() {
	playerPawn->AcceptCard();

}

void UMyUserWidget::despawnCard() {
	hidden = false;
	playerPawn->DespawnCard();

}

void UMyUserWidget::declineCard() {
	playerPawn->declineCard();

}

void UMyUserWidget::setShowNotYourPiece(bool show) {
	if (isHudAvaliable()) {
		showNotYourPiece = show;
	}
}

void UMyUserWidget::setMustTakePiece(bool show) {
	if (isHudAvaliable()) {
		showMustTakePiece = show;
	}
}

void UMyUserWidget::setCanOnlyMovePiece(bool show) {
	if (isHudAvaliable()) {
		showCanOnlyMovePiece = show;
	}
}

void UMyUserWidget::showEnd(int player) {
	if (isHudAvaliable()) {

		gameOver = true;
		if (player == 1)
			playerOneWins = true;
		if (player == 0)
			playerOneWins = false;
	}
}

bool UMyUserWidget::isHudAvaliable() {
	if (this == nullptr) {
		return false;
	} else {
		return true;
	}
}

void UMyUserWidget::setHidden(bool hide) {
	hidden = hide;
}

void UMyUserWidget::toggleHUD() {
	hideHUD = !hideHUD;
}

void UMyUserWidget::showDoubleJumpNotice() {
	doubleJumpShow = true;

	FTimerHandle UnusedHandle;
	playerPawn->GetWorldTimerManager().SetTimer(UnusedHandle, this, &UMyUserWidget::hideDoubleJumpNotice, 3.0, false);
}

void UMyUserWidget::hideDoubleJumpNotice() {
	doubleJumpShow = false;
}

void UMyUserWidget::showRunOutOfTime() {
	runOutOfTimeShow = true;

	FTimerHandle UnusedHandle;
	playerPawn->GetWorldTimerManager().SetTimer(UnusedHandle, this, &UMyUserWidget::hideRunOutOfTime, 3.0, false);
}

void UMyUserWidget::hideRunOutOfTime() {
	runOutOfTimeShow = false;
}