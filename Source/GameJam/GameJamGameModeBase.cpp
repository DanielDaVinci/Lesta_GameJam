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

FString AGameJamGameModeBase::GetCurrentTime() const
{
	if (!GameSessionTimer)
		return "00 : 00";

	return GameSessionTimer->GetCurrentTime();
}

void AGameJamGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (GameSessionTimerClass)
	{
		ClearPause();
		GameSessionTimer = NewObject<UGameSessionTimer>(this, GameSessionTimerClass);
		GameSessionTimer->InitializeTimer(GetWorld());
	}
}

void AGameJamGameModeBase::StartPlay()
{
	Super::StartPlay();

	SetGameInput();
}

void AGameJamGameModeBase::SetGameInput() const
{
	const auto playerController = GetWorld()->GetFirstPlayerController();
	if (!playerController)
		return;
	
	playerController->SetInputMode(FInputModeGameOnly());
	playerController->SetShowMouseCursor(false);
}

void AGameJamGameModeBase::SetUIInput() const
{
	const auto playerController = GetWorld()->GetFirstPlayerController();
	if (!playerController)
		return;
	
	playerController->SetInputMode(FInputModeUIOnly());
	playerController->SetShowMouseCursor(true);
}

