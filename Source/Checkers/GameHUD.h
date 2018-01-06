// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetBlueprint.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class CHECKERS_API UGameHUD : public UWidgetBlueprint
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SomeText)
	FString Test1234;
	
	
};
