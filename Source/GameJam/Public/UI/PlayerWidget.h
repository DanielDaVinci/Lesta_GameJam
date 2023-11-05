// Lesta GameJam, Lazy Pixel. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

UCLASS()
class GAMEJAM_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetCampfirePower(int32 ProgressIndex) const;
};
