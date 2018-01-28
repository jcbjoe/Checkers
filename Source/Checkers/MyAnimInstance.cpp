// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"


UMyAnimInstance::UMyAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), hitting(false)
{

}

void UMyAnimInstance::setHit(bool hittingHere) {
	hitting = hittingHere;
}