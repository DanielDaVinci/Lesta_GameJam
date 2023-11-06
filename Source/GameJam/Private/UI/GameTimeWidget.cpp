// Lesta GameJam, Lazy Pixel. All Rights Reserved


#include "UI/GameTimeWidget.h"
#include "GameJam/GameJamGameModeBase.h"

FString UGameTimeWidget::GetRemainingTime() const
{
	const auto GameMode = Cast<AGameJamGameModeBase>(GetWorld()->GetAuthGameMode());

	return GameMode->GetCurrentTime();
}
