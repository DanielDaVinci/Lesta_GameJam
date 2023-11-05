// Lesta GameJam, Lazy Pixel. All Rights Reserved


#include "UI/CampfireWidget.h"

#include "PowerComponent.h"
#include "CentralObjects/Campfire.h"
#include "GameJam/GameJamGameModeBase.h"

float UCampfireWidget::GetCampfirePower(int32 ProgressIndex) const
{
	const auto GameMode = Cast<AGameJamGameModeBase>(GetWorld()->GetAuthGameMode());
	const ACampfire* Campfire = GameMode->GetCampfire();
	if (!Campfire)
		return 0.0f;

	const auto Component = Campfire->GetComponentByClass(UPowerComponent::StaticClass());
	const auto PowerComponent = Cast<UPowerComponent>(Component);
	if (!PowerComponent)
		return 0.0f;
    
	const float CurProgPower = PowerComponent->GetPower() * 10 - ProgressIndex;
	return CurProgPower;
}
