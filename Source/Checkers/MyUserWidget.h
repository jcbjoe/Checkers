// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	FString CurrentPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SomeText)
	FString AlertMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SomeText)
	int delayTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SomeText)
	bool showAlertMessage;
	
	void setPlayer1Time(FString time);

	void setPlayer2Time(FString time);

	void setGlobalTime(FString time);

	void setPlayer1Score(FString time);

	void setPlayer2Score(FString time);

	void setCurrentPlayer(FString time);

	void setAlertMessage(FString message, int displayTime);

};
