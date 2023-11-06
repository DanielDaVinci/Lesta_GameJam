// Lesta GameJam, Lazy Pixel. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

UCLASS()
class GAMEJAM_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
	public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsBranchVisible(int32 BranchNum) const;
};
