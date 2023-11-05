// Lesta GameJam, Lazy Pixel. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameSessionTimer.generated.h"

DECLARE_DELEGATE_OneParam(FOnTimeTick, int32)

UCLASS()
class GAMEJAM_API UGameSessionTimer : public UObject
{
	GENERATED_BODY()

public:
	FOnTimeTick OnTimeTick;
	int32 TimeRemain = 10;
	UGameSessionTimer();
	FString GetCurrentTime();
	void InitializeTimer(UWorld* world);

private:
	UPROPERTY()
	UWorld* World;
	FTimerHandle Handle;
	void SetInstanceOnGameMode();
	void OnTimerTicked();
};
