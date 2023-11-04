// Lesta GameJam, Lazy Pixel. All Rights Reserved


#include "Pickable/PowerPickup.h"

// Sets default values
APowerPickup::APowerPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APowerPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

