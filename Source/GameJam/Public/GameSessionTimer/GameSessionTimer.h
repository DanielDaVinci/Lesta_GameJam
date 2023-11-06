// Lesta GameJam, Lazy Pixel. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameSessionTimer.generated.h"

UCLASS()
class GAMEJAM_API UGameSessionTimer : public UObject
{
	GENERATED_BODY()

public:
	FString GetCurrentTime() const;
	
	void InitializeTimer(UWorld* world);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	float GameSessionTime = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	float TimerFrequency = 0.01f;

private:
	FTimerHandle Handle;
	float TimeRemain = 300;
	
	UPROPERTY()
	UWorld* World;
	
	void OnTimerTicked();
	
	bool PlayerInLight() const;
};
