// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyUserWidget.h"
#include "MyPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class CHECKERS_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> wMainMenu;

	// Variable to hold the widget After Creating it.
	UMyUserWidget* MyMainMenu;

	UUserWidget* Editor;

	virtual void BeginPlay();

	UMyUserWidget* getHudWidget();
	
};
