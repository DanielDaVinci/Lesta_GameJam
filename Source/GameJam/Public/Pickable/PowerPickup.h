// Lesta GameJam, Lazy Pixel. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerPickup.generated.h"

UCLASS()
class GAMEJAM_API APowerPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerPickup();

protected:
	UStaticMeshComponent* staticMeshComponent;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
