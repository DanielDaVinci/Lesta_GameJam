// Lesta GameJam, Lazy Pixel. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "LightSource.generated.h"

//class USkeletalMeshComponent;
//class UPointLightComponent;

UCLASS()
class GAMEJAM_API ALightSource : public AActor
{
	GENERATED_BODY()
	
public:	
	ALightSource();

	void ReloadTorch();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UPointLightComponent* PointLight;

	FTimerHandle m_Timer;
	int32 m_nSec = 48;

	void DecreaseFire();
	virtual void BeginPlay() override;
};
