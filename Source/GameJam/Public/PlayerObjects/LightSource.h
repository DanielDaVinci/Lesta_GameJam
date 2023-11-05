// Lesta GameJam, Lazy Pixel. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "LightSource.generated.h"

class UPowerComponent;

UCLASS()
class GAMEJAM_API ALightSource : public AActor
{
	GENERATED_BODY()
	
public:	
	ALightSource();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UPointLightComponent* PointLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UPowerComponent* PowerComponent;

	virtual void BeginPlay() override;

};
