// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"




void AMyPlayerController::BeginPlay() {

	Super::BeginPlay();

	UserInterface = CreateWidget<UMyUserWidget>(this, UMyUserWidget::StaticClass());
	UserInterface->AddToViewport(9999); // Z-order, this just makes it render on the very top.

}