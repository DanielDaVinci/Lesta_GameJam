// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameSessionTimer/GameSessionTimer.h"
#include "GameJamGameModeBase.generated.h"

class ACampfire;

UCLASS()
class GAMEJAM_API AGameJamGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameJamGameModeBase();

	void SetCampFire(ACampfire* NewCampFire) { Campfire = NewCampFire; }
	ACampfire* GetCampfire() const { return Campfire; }
	void SetGameSessionTimer(UGameSessionTimer* NewGameSessionTimer) { GameSessionTimer = NewGameSessionTimer; }
	UGameSessionTimer* GetGameSessionTimer() const { return GameSessionTimer; }

protected:
	virtual void BeginPlay() override;
	virtual void StartPlay() override;
	
private:
	UPROPERTY()
	ACampfire* Campfire;
	UPROPERTY()
	UGameSessionTimer* GameSessionTimer;
};
