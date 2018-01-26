// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CHECKERS_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
		UMyAnimInstance(const FObjectInitializer&);
public:
	void setHit(bool);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ANIMBP")
	bool hitting;

private:

	
	
};
