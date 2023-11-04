// Lesta GameJam, Lazy Pixel. All Rights Reserved


#include "PlayerObjects/LightSource.h"

ALightSource::ALightSource()
{
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>("TorchMesh");
	SetRootComponent(BaseMesh);
	
	PointLight = CreateDefaultSubobject<UPointLightComponent>("TorchLight");
	PointLight->SetupAttachment(BaseMesh);
	PointLight->SetRelativeLocation(FVector(0, 0, 80.0f));
}

void ALightSource::BeginPlay()
{
	Super::BeginPlay();
	ReloadTorch();
}

void ALightSource::ReloadTorch()
{
	PointLight->SetIntensity(6000);
	GetWorldTimerManager().SetTimer(m_Timer, this, &ALightSource::DecreaseFire, 0.25, true, .0f);
}

void ALightSource::DecreaseFire()
{
	if (--m_nSec <= 0)
	{
		GetWorldTimerManager().ClearTimer(m_Timer);
		Destroy();
	}
	PointLight->SetIntensity(PointLight->Intensity - 125);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Intensity %f"), PointLight->Intensity));
}
