// Lesta GameJam, Lazy Pixel. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PickupAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNotifiedSignature)

UCLASS()
class GAMEJAM_API UPickupAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	FOnNotifiedSignature OnNotified;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
