// Lesta GameJam, Lazy Pixel. All Rights Reserved

#include "CentralObjects/Campfire.h"

#include "MainCharacter.h"
#include "PowerComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameJam/GameJamGameModeBase.h"
#include "Kismet/GameplayStatics.h"

ACampfire::ACampfire()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(GetRootComponent());
	
	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	PointLightComponent->SetupAttachment(GetRootComponent());
	PointLightComponent->AttenuationRadius = 800.0f;
	PointLightComponent->bUseInverseSquaredFalloff = false;
	PointLightComponent->LightFalloffExponent = 1.0f;
	
	LifeLightSphereComponent = CreateDefaultSubobject<USphereComponent>("LifeLightSphereComponent");
	LifeLightSphereComponent->SetupAttachment(GetRootComponent());
	LifeLightSphereComponent->InitSphereRadius(800.0f);
	LifeLightSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LifeLightSphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);

	InteractSphereComponent = CreateDefaultSubobject<USphereComponent>("InteractSphereComponent");
	InteractSphereComponent->SetupAttachment(GetRootComponent());
	InteractSphereComponent->InitSphereRadius(150.0f);
	InteractSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractSphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);

	InteractWidget = CreateDefaultSubobject<UWidgetComponent>("InteractWidgetComponent");
	InteractWidget->SetupAttachment(GetRootComponent());
	InteractWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InteractWidget->SetDrawAtDesiredSize(true);
	InteractWidget->SetVisibility(false);

	ReloadWidget = CreateDefaultSubobject<UWidgetComponent>("ReloadWidgetComponent");
	ReloadWidget->SetupAttachment(GetRootComponent());
	ReloadWidget->SetWidgetSpace(EWidgetSpace::Screen);
	ReloadWidget->SetDrawAtDesiredSize(true);
	ReloadWidget->SetVisibility(false);
	
	PowerComponent = CreateDefaultSubobject<UPowerComponent>("PowerComponent");
}

void ACampfire::NotifyActorBeginInteractOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const auto MainCharacter = Cast<AMainCharacter>(OtherActor);
	if (!MainCharacter)
		return;

	ReloadWidget->SetVisibility(true);
	MainCharacter->OnReload.BindUObject(this, &ACampfire::Reload);
	
	if (MainCharacter->GetBranchesAmount() == 0)
		return;
	
	InteractWidget->SetVisibility(true);
	MainCharacter->OnInteract.BindUObject(this, &ACampfire::Interact);
}

void ACampfire::NotifyActorEndInteractOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const auto MainCharacter = Cast<AMainCharacter>(OtherActor);
	if (!MainCharacter)
		return;

	InteractWidget->SetVisibility(false);
	MainCharacter->OnInteract.Unbind();
	
	ReloadWidget->SetVisibility(false);
	MainCharacter->OnReload.Unbind();
}

void ACampfire::BeginPlay()
{
	Super::BeginPlay();

	MaxLifeLightRadius = PointLightComponent->AttenuationRadius;
	MaxLightIntensity = PointLightComponent->Intensity;

	InteractSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ACampfire::NotifyActorBeginInteractOverlap);
	InteractSphereComponent->OnComponentEndOverlap.AddDynamic(this, &ACampfire::NotifyActorEndInteractOverlap);
	PowerComponent->OnValueUpdate.BindUObject(this, &ACampfire::OnPowerChangeValue);
	
	SetInstanceOnGameMode();
}

void ACampfire::SetInstanceOnGameMode()
{
	if (!GetWorld())
		return;
	
	const auto GameMode = Cast<AGameJamGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode)
		return;

	GameMode->SetCampFire(this);
}

void ACampfire::OnPowerChangeValue(float Percent)
{
	float newRadius = Percent * MaxLifeLightRadius;
	PointLightComponent->SetAttenuationRadius(newRadius);

	float newIntensity = Percent * MaxLightIntensity;
	PointLightComponent->SetIntensity(newIntensity);
}

void ACampfire::Interact(ACharacter* Character)
{
	const auto MainCharacter = Cast<AMainCharacter>(Character);
	if (!MainCharacter)
		return;

	PowerComponent->AddPower(MainCharacter->GetBranchesAmount() * PercentOneBranch);
	MainCharacter->PutAllBranches();

	InteractWidget->SetVisibility(false);
}

void ACampfire::Reload(ACharacter* Character)
{
	const auto MainCharacter = Cast<AMainCharacter>(Character);
	if (!MainCharacter)
		return;
	
	MainCharacter->ExternalReloadTorch();
}

