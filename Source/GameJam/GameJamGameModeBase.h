// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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
	
private:
	UPROPERTY()
	ACampfire* Campfire;
};
