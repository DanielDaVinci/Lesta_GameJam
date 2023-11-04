// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PowerComponent.h"

UPowerComponent::UPowerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UPowerComponent::BeginPlay()
{
	Super::BeginPlay();
}
