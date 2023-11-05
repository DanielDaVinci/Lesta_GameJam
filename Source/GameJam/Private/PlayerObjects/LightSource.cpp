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
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	PointLight = CreateDefaultSubobject<UPointLightComponent>("TorchLight");
	PointLight->SetupAttachment(GetRootComponent());
	PointLight->SetRelativeLocation(FVector(0, 0, 80));

	PowerComponent = CreateDefaultSubobject<UPowerComponent>("PowerComponent");
}

void ALightSource::Repower() const
{
	PowerComponent->SetPower(1.0f);
}

void ALightSource::Detach()
{
	FDetachmentTransformRules detachRules(EDetachmentRule::KeepWorld, false);
	DetachFromActor(detachRules);
	EnablePhysics();

	StartTimerDestroy();
}

void ALightSource::EnablePhysics() const
{
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	StaticMeshComponent->SetSimulatePhysics(true);
}

void ALightSource::StartTimerDestroy()
{
	currentTime = TimeLifeAfterDetach;
	maxIntensity = PointLight->Intensity;
	
	GetWorldTimerManager().SetTimer(DestroyTimer, this, &ALightSource::TimerDestroyUpdate, TimerFrequency, true);
}

void ALightSource::TimerDestroyUpdate()
{
	currentTime -= TimerFrequency / TimeLifeAfterDetach;
	currentTime = FMath::Max(currentTime, 0.0f);
	
	PointLight->SetIntensity(currentTime / TimeLifeAfterDetach * maxIntensity);
	
	if (currentTime <= 0.0f)
	{
		GetWorldTimerManager().ClearTimer(DestroyTimer);
		Destroy();
	}
}

void ALightSource::BeginPlay()
{
	Super::BeginPlay();

	PowerComponent->OnPowerEnd.AddUObject(this, &ALightSource::OnPowerEnd);
}

void ALightSource::OnPowerEnd()
{
	OnBurnOut.ExecuteIfBound();
}

