// Lesta GameJam, Lazy Pixel. All Rights Reserved


#include "PlayerObjects/LightSource.h"

// Sets default values
ALightSource::ALightSource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALightSource::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightSource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

