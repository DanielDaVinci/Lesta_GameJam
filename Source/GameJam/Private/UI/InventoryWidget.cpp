// Lesta GameJam, Lazy Pixel. All Rights Reserved


#include "UI/InventoryWidget.h"
#include "Player/MainCharacter.h"

bool UInventoryWidget::IsBranchVisible(int32 BranchNum) const
{
    const auto Player = Cast<AMainCharacter>(GetOwningPlayerPawn());
    if (!Player) return false;

    return Player->GetBranchesAmount() >= BranchNum;
}