// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerComponent.generated.h"

DECLARE_DELEGATE_OneParam(FOnValueUpdate, float)
DECLARE_MULTICAST_DELEGATE(FOnPowerEnd)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMEJAM_API UPowerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FOnValueUpdate OnValueUpdate;
	FOnPowerEnd OnPowerEnd;

	UPowerComponent();
	
	void AddPower(float Percent);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", meta = (ClampMin = "0.0"))
	float BurningTime = 60.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float TimeUpdateValueFrequency = 0.01f;

	virtual void BeginPlay() override;

private:
	float currentPower;
	FTimerHandle PowerTimer;

	void StartPowerTimer();
	void PowerTimerUpdate();
};
