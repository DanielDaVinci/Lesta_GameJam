// Lesta GameJam, Lazy Pixel. All Rights Reserved


#include "Pickable/PowerPickup.h"

#include "MainCharacter.h"
#include "Components/BoxComponent.h"
#include "Player/MainCharacter.h"
#include "Components/WidgetComponent.h"

APowerPickup::APowerPickup()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("TorchMesh");
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollisionComponent");
	BoxCollision->SetupAttachment(GetRootComponent());
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Overlap);

	InteractWidget = CreateDefaultSubobject<UWidgetComponent>("InteractWidgetComponent");
	InteractWidget->SetupAttachment(GetRootComponent());
	InteractWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InteractWidget->SetDrawAtDesiredSize(true);
}

void APowerPickup::BeginPlay()
{
	Super::BeginPlay();

	InteractWidget->SetVisibility(false);
}

void APowerPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto MainCharacter = Cast<AMainCharacter>(OtherActor);
	if (!MainCharacter)
		return;

	if (CanPickup())
	{
		InteractWidget->SetVisibility(true);
	}
	
	MainCharacter->OnInteract.BindUObject(this, &APowerPickup::Pickup);
}

void APowerPickup::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	const auto MainCharacter = Cast<AMainCharacter>(OtherActor);
	if (!MainCharacter)
		return;

	InteractWidget->SetVisibility(false);
	
	MainCharacter->OnInteract.Unbind();
}

void APowerPickup::Pickup(ACharacter* Character)
{
	auto MainCharacter = Cast<AMainCharacter>(Character);
	if (!MainCharacter)
		return;

	if (!CanPickup())
		return;

	if (MainCharacter->AddBranch())
	{
		StaticMeshComponent->SetVisibility(false);
		InteractWidget->SetVisibility(false);
	}
}

bool APowerPickup::CanPickup() const
{
	return StaticMeshComponent->IsVisible();
}

