// Lesta GameJam, Lazy Pixel. All Rights Reserved


#include "PlayerObjects/LightSource.h"
#include "PowerComponent.h"

ALightSource::ALightSource()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("TorchMesh");
	StaticMeshComponent->SetupAttachment(GetRootComponent());
	
	PointLight = CreateDefaultSubobject<UPointLightComponent>("TorchLight");
	PointLight->SetupAttachment(GetRootComponent());
	PointLight->SetRelativeLocation(FVector(0, 0, 80));

	PowerComponent = CreateDefaultSubobject<UPowerComponent>("PowerComponent");
}

void ALightSource::BeginPlay()
{
	Super::BeginPlay();
	
}

