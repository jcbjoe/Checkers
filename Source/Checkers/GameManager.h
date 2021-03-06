// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "MyPlayerController.h"
#include "CheckerboardManager.h"
#include "GameManager.generated.h"

UCLASS()
class CHECKERS_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int getCurrentPlayer();

	int getOtherPlayer();

	UMyUserWidget* getUI();

	void endTurn();

	void PauseTimer(bool pause);

	bool isInCardMenu();

	void setIsInCardMenu(bool val);

	ACheckerboardManager* getCheckerboardManager();

	void setPlayer0MissTurn(bool);
	void setPlayer1MissTurn(bool);

	bool isPlayer0MissingTurn();

	bool isPlayer1MissingTurn();

	void endGame();

	void resetTimer();

	void setGlobalPause(bool pause);

	bool hasMadeChoice();

	void makeChoice(bool);

private:
	int lastSecond;

	AMyPlayerController* getPlayerController();
	
	int seconds;

	ACheckerboardManager* checkerBoardManager;
	
	void tickTimer();

	int playersTurn;

	void startTurn();

	bool playerTimerOn;
	int playerTimerCurrentSeconds;

	bool paused;

	bool inCardMenu;

	bool player0MissTurn;
	bool player1MissTurn;

	bool globalPause;

	bool madeChoice;
};
