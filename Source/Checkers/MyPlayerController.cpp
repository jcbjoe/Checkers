// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMyPlayerController::BeginPlay() {

	Super::BeginPlay();

	pausedGlobal = false;

	if (wMainMenu) // Check if the Asset is assigned in the blueprint.
	{

		// Create the widget and store it.
		MyMainMenu = CreateWidget<UMyUserWidget>(this, wMainMenu);


		// now you can use the widget directly since you have a referance for it.
		// Extra check to  make sure the pointer holds the widget.
		if (MyMainMenu)
		{
			//let add it to the view port
			MyMainMenu->AddToViewport();
		}

		//Show the Cursor.
		bShowMouseCursor = true;
	}

}

bool AMyPlayerController::isHudAvaliable() {
	if (MyMainMenu)
	{
		return true;
	}
	else {
		return false;
	}
}

UMyUserWidget* AMyPlayerController::getHudWidget() {
	return MyMainMenu;
}

void AMyPlayerController::pauseGameTest(bool pause) {
	pausedGlobal = pause;
	((APlayerPawn*)((AMyPlayerController*)(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetPawn()))->setPaused(pause);
}

bool AMyPlayerController::isPaused() {
	return pausedGlobal;
}