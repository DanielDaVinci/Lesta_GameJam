// Lesta GameJam, Lazy Pixel. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CampfireWidget.generated.h"

UCLASS()
class GAMEJAM_API UCampfireWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetCampfirePower(int32 ProgressIndex) const;
};
