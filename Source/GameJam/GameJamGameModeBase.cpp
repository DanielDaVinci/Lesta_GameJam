// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameJamGameModeBase.h"

#include "GameHUD.h"
#include "MainCharacter.h"
#include "MainPlayerController.h"


AGameJamGameModeBase::AGameJamGameModeBase()
{
	DefaultPawnClass = AMainCharacter::StaticClass();
	PlayerControllerClass = AMainPlayerController::StaticClass();
	HUDClass = AGameHUD::StaticClass();
}

void AGameJamGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GameSessionTimer = NewObject<UGameSessionTimer>();
}

void AGameJamGameModeBase::StartPlay()
{
	Super::StartPlay();
	GameSessionTimer->InitializeTimer(GetWorld());
}

