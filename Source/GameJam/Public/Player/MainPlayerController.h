// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

UCLASS()
class GAMEJAM_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin="0.0", ClampMax="500.0"))
	float RotationSpeed = 100.0f;
	
	virtual void BeginPlay() override;

public:
	virtual void SetupInputComponent() override;

	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

private:
	FVector inputDirection{0.0, 0.0, 0.0,};
	
	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void RotateToVelocityDirection(float DeltaTime);
};
