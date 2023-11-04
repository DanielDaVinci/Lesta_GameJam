// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEJAM_API UPowerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPowerComponent();

protected:
	virtual void BeginPlay() override;

		
};
