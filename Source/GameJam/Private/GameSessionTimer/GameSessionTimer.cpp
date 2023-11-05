// Lesta GameJam, Lazy Pixel. All Rights Reserved

#include "GameSessionTimer/GameSessionTimer.h"
#include "GameJam/GameJamGameModeBase.h"

UGameSessionTimer::UGameSessionTimer()
{
	SetInstanceOnGameMode();
}

void UGameSessionTimer::InitializeTimer(UWorld* world)
{
	World = world;
	World->GetTimerManager().SetTimer(Handle, this, &UGameSessionTimer::OnTimerTicked, 1.0f, true);
}

void UGameSessionTimer::SetInstanceOnGameMode()
{
	if (!World)
		return;
	
	const auto GameMode = Cast<AGameJamGameModeBase>(World->GetAuthGameMode());
	if (!GameMode)
		return;

	GameMode->SetGameSessionTimer(this);
}

FString UGameSessionTimer::GetCurrentTime()
{
	int32 minutes = TimeRemain / 60;
	int32 seconds = TimeRemain % 60;
	FString formattedTime = FString::Printf(TEXT("%02d : %02d"), minutes, seconds);
	UE_LOG(LogTemp, Warning, TEXT("MyTimeValue: %s"), * formattedTime);
	return formattedTime;
}

void UGameSessionTimer::OnTimerTicked()
{
	TimeRemain -= 1;
	OnTimeTick.ExecuteIfBound(TimeRemain);

	if (TimeRemain <= 0)
	{
		World->GetTimerManager().ClearTimer(Handle);
	}

	GetCurrentTime();
}
