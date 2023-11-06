// Lesta GameJam, Lazy Pixel. All Rights Reserved


#include "Animations/PickupAnimNotify.h"

void UPickupAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast();
	Super::Notify(MeshComp, Animation);
}
