// Copyright Epic Games, Inc. All Rights Reserved.


#include "PoCGrappinGameModeBase.h"

void APoCGrappinGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello !!!!!!!!!!!!!!!!!!!!!!!!!"));

}