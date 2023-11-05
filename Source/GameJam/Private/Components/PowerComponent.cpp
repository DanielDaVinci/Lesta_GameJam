// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PowerComponent.h"

UPowerComponent::UPowerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPowerComponent::AddPower(float Percent)
{
	currentPower = FMath::Clamp(currentPower + Percent, 0.0f, 1.0f);
}


void UPowerComponent::BeginPlay()
{
	Super::BeginPlay();

	currentPower = 1.0f;
	StartPowerTimer();
}

void UPowerComponent::StartPowerTimer()
{
	if (!GetOwner())
		return;

	GetOwner()->GetWorldTimerManager().SetTimer(PowerTimer, this, &UPowerComponent::PowerTimerUpdate,
	                                            TimeUpdateValueFrequency, true);
}

void UPowerComponent::PowerTimerUpdate()
{
	const float timerDecrement = TimeUpdateValueFrequency / BurningTime;
	currentPower -= timerDecrement;
	currentPower = FMath::Max(currentPower, 0.0f);

	OnValueUpdate.ExecuteIfBound(currentPower);

	if (currentPower <= 0.0f)
	{
		if (!GetOwner())
			return;

		GetOwner()->GetWorldTimerManager().ClearTimer(PowerTimer);

		OnPowerEnd.Broadcast();
	}
}
