// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerPawn.h"
#include "CoreMinimal.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIBP")
	FString Player1Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIBP")
	FString Player2Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIBP")
	FString GlobalTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIBP")
	FString Player1Score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIBP")
	FString Player2Score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIBP")
	int CurrentPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIBP")
	FString AlertMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIBP")
	int delayTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIBP")
	bool showAlertMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIBP")
	bool hidden;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIBP")
	bool take;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIBP")
	bool buttonPressed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIBP")
	bool showNotYourPiece;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIBP")
	bool gameOver;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIBP")
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
	void acceptCard();

	UFUNCTION(BlueprintCallable)
	void declineCard();

	void showEnd(int player);

	void turnOffAlert();

private:
	bool isHudAvaliable();
};
