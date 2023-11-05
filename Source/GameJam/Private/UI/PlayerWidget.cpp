// Lesta GameJam, Lazy Pixel. All Rights Reserved


#include "UI/PlayerWidget.h"

#include "MainCharacter.h"
#include "../GameJamGameModeBase.h"

bool UPlayerWidget::IsPlayerInLight() const
{
	const auto player = Cast<AMainCharacter>(GetOwningPlayerPawn());
	if (!player)
		return false;

	return player->InLight();
}

bool UPlayerWidget::IsTimerEnd() const
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode())
		return false;

	const auto gameMode = Cast<AGameJamGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!gameMode)
		return false;

	return gameMode->GetCurrentTime() == "00 : 00";
}
