// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainCharacter.h"

#include "LightSource.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameJam/GameJamGameModeBase.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	SpringArmComponent->TargetArmLength = 500.0f;
	SpringArmComponent->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

bool AMainCharacter::AddBranch()
{
	if (currentBranches >= MaxAmountBranches)
		return false;

	// TODO(Animation)

	currentBranches++;
	UE_LOG(LogTemp, Display, TEXT("%i"), currentBranches);
	return true;
}

void AMainCharacter::ReloadTorch()
{
	// TODO()
}

void AMainCharacter::PutAllBranches()
{
	// TODO(Animation)

	currentBranches = 0;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	CreateLightSource();
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::Interact);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AMainCharacter::Reload);
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainCharacter::Interact()
{
	OnInteract.ExecuteIfBound(this);
}

void AMainCharacter::Reload()
{
	OnReload.ExecuteIfBound(this);
}

void AMainCharacter::CreateLightSource()
{
	if (!GetWorld() || !GetMesh())
		return;

	const auto LightSource = GetWorld()->SpawnActor<ALightSource>(LightSourceClass);
	if (!LightSource)
		return;

	LightSource->SetOwner(this);
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	LightSource->AttachToComponent(GetMesh(), AttachmentRules, LightSourceSocketName);
}
