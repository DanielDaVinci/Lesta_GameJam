// Lesta GameJam, Lazy Pixel. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Campfire.generated.h"

class UWidgetComponent;
class UPowerComponent;
class USphereComponent;
class UPointLightComponent;

UCLASS()
class GAMEJAM_API ACampfire : public AActor
{
	GENERATED_BODY()
	
public:	
	ACampfire();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UPointLightComponent* PointLightComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* LifeLightSphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* InteractSphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* InteractWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* ReloadWidget;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UPowerComponent* PowerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", meta = (ClampMin="0.0", ClampMax="1.0"))
	float PercentOneBranch = 0.1f;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void NotifyActorBeginInteractOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void NotifyActorEndInteractOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	float MaxLifeLightRadius;
	float MaxLightIntensity;

	void SetInstanceOnGameMode();
	void OnPowerChangeValue(float Percent);

	void Interact(ACharacter* Character);
	void Reload(ACharacter* Character);
};
