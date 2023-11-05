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
	World->GetTimerManager().SetTimer(Handle, this, &UGameSessionTimer::OnTimerTicked, 1.0f, true);
}

FString UGameSessionTimer::GetCurrentTime() const
{
	const int32 minutes = TimeRemain / 60;
	const int32 seconds = TimeRemain % 60;
	FString formattedTime = FString::Printf(TEXT("%02d : %02d"), minutes, seconds);
	
	return formattedTime;
}

void UGameSessionTimer::OnTimerTicked()
{
	TimeRemain -= 1;

	if (TimeRemain <= 0 || !PlayerInLight())
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
