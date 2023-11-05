// Lesta GameJam, Lazy Pixel. All Rights Reserved


#include "UI/TorchWidget.h"
#include "Player/MainCharacter.h"
#include "PlayerObjects/LightSource.h"
#include "Components/PowerComponent.h"

float UTorchWidget::GetTorchPower() const
{
    const auto Player = Cast<AMainCharacter>(GetOwningPlayerPawn());
    if (!Player) return 0.0f;

    const ALightSource* Torch = Player->GetCurrentLightSource();
    if (!Torch) return 0.0f;

    const auto Component = Torch->GetComponentByClass(UPowerComponent::StaticClass());
    const auto PowerComponent = Cast<UPowerComponent>(Component);
    if (!PowerComponent) return 0.0f;

    return PowerComponent->GetPower();
}
