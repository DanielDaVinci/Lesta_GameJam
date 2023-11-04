// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainPlayerController.h"

#include "MainCharacter.h"
#include "GameFramework/Character.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAxis("MoveForward", this, &AMainPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMainPlayerController::MoveRight);
}

void AMainPlayerController::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	RotateToVelocityDirection(DeltaTime);
}


void AMainPlayerController::MoveForward(float Amount)
{
	inputDirection.Y = -1 * Amount;
	GetCharacter()->AddMovementInput(GetCharacter()->GetActorForwardVector(), Amount);
}

void AMainPlayerController::MoveRight(float Amount)
{
	inputDirection.X = Amount;
	GetCharacter()->AddMovementInput(GetCharacter()->GetActorRightVector(), Amount);
}

void AMainPlayerController::RotateToVelocityDirection(float DeltaTime)
{
	if (FMath::IsNearlyZero(inputDirection.Size()))
		return;

	const auto mesh = GetCharacter() ? GetCharacter()->GetMesh() : nullptr;
	if (!mesh)
		return;
	
	const auto currentMeshVector = mesh->GetForwardVector();
	const auto needMeshVector = inputDirection.GetSafeNormal2D();

	float yawAngle = FMath::Acos(FVector::DotProduct(currentMeshVector, needMeshVector));
	yawAngle *= FMath::Sign(FVector::CrossProduct(currentMeshVector, needMeshVector).Z);

	auto meshRotation = mesh->GetRelativeRotation();
	meshRotation.Yaw += yawAngle * DeltaTime * RotationSpeed;

	mesh->SetRelativeRotation(meshRotation);
}
