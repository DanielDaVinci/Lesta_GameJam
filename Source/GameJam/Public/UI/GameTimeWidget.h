// Lesta GameJam, Lazy Pixel. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameTimeWidget.generated.h"

UCLASS()
class GAMEJAM_API UGameTimeWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	FString GetRemainingTime() const;
};
