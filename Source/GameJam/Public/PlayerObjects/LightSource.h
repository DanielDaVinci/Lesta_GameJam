// Lesta GameJam, Lazy Pixel. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "LightSource.generated.h"

class UPowerComponent;

DECLARE_DELEGATE(FOnBurnOut)

UCLASS()
class GAMEJAM_API ALightSource : public AActor
{
	GENERATED_BODY()

public:
	FOnBurnOut OnBurnOut;

	ALightSource();

	void Repower() const;
	void Detach();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UPointLightComponent* PointLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UPowerComponent* PowerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Destroy")
	float TimeLifeAfterDetach = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Destroy")
	float TimerFrequency = 0.01f;
	
	virtual void BeginPlay() override;

private:
	float currentTime;
	float maxIntensity;
	FTimerHandle DestroyTimer;
	
	void OnPowerEnd();

	void EnablePhysics() const;

	void StartTimerDestroy();
	void TimerDestroyUpdate();
};
