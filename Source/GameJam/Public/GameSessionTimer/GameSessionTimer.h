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
	int32 GameSessionTime = 300;

private:
	FTimerHandle Handle;
	int32 TimeRemain = 300;
	
	UPROPERTY()
	UWorld* World;
	
	void OnTimerTicked();
	
	bool PlayerInLight() const;
};
