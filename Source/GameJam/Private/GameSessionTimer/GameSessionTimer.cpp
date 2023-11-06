// Lesta GameJam, Lazy Pixel. All Rights Reserved

#include "GameSessionTimer/GameSessionTimer.h"

#include "MainCharacter.h"
#include "GameJam/GameJamGameModeBase.h"

void UGameSessionTimer::InitializeTimer(UWorld* world)
{
	if (!world)
		return;

	TimeRemain = GameSessionTime;
	
	World = world;
	World->GetTimerManager().SetTimer(Handle, this, &UGameSessionTimer::OnTimerTicked, TimerFrequency, true);
}

FString UGameSessionTimer::GetCurrentTime() const
{
	const int32 minutes = FMath::CeilToInt(TimeRemain) / 60;
	const int32 seconds = FMath::CeilToInt(TimeRemain) % 60;
	FString formattedTime = FString::Printf(TEXT("%02d : %02d"), minutes, seconds);
	
	return formattedTime;
}

void UGameSessionTimer::OnTimerTicked()
{
	TimeRemain -= TimerFrequency / GameSessionTime;
	TimeRemain = FMath::Max(TimeRemain, 0.0f);
	
	if (FMath::IsNearlyZero(TimeRemain) || !PlayerInLight())
	{
		World->GetTimerManager().ClearTimer(Handle);
		
		const auto gameMode = Cast<AGameJamGameModeBase>(World->GetAuthGameMode());
		if (!gameMode)
			return;

		gameMode->SetPause(World->GetFirstPlayerController());
		gameMode->SetUIInput();
	}
}

bool UGameSessionTimer::PlayerInLight() const
{
	if (!World || !World->GetFirstPlayerController())
		return false;
	
	const auto player = Cast<AMainCharacter>(World->GetFirstPlayerController()->GetCharacter());
	if (!player)
		return false;

	return player->InLight();
}
