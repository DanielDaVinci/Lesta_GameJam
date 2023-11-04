// Lesta GameJam, Lazy Pixel. All Rights Reserved

#include "CentralObjects/Campfire.h"

#include "PowerComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"

ACampfire::ACampfire()
{
	PrimaryActorTick.bCanEverTick = false;
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(GetRootComponent());
	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	PointLightComponent->SetupAttachment(GetRootComponent());
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(GetRootComponent());
	SphereComponent->InitSphereRadius(50.0f);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	PowerComponent = CreateDefaultSubobject<UPowerComponent>("PowerComponent");
}

void ACampfire::BeginPlay()
{
	Super::BeginPlay();
	
}