// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerPawn.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHECKERS_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;


	APlayerPawn* playerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SomeText)
	FString Player1Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SomeText)
	FString Player2Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SomeText)
	FString GlobalTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SomeText)
	FString Player1Score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SomeText)
	FString Player2Score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SomeText)
	int CurrentPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SomeText)
	FString AlertMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SomeText)
	int delayTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SomeText)
	bool showAlertMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SomeText)
	bool hidden;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SomeText)
	bool take;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SomeText)
	bool buttonPressed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SomeText)
	bool showNotYourPiece;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SomeText)
	bool gameOver;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SomeText)
	bool playerOneWins;
	
	void setPlayer1Time(FString time);

	void setPlayer2Time(FString time);

	void setGlobalTime(FString time);

	void setPlayer1Score(FString time);

	void setPlayer2Score(FString time);

	void setCurrentPlayer(int time);

	void setAlertMessage(FString message, int displayTime);

	void spawnCardText();

	void setShowNotYourPiece(bool show);

	UFUNCTION(BlueprintCallable)
	void despawnCard();

	UFUNCTION(BlueprintCallable)
	void rotateCard();

	void showEnd(int player);

	void turnOffAlert();
};
