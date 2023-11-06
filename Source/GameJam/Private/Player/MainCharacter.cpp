// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainCharacter.h"

#include "LightSource.h"
#include "MainPlayerController.h"
#include "Animations/EndPickupAnimNotify.h"
#include "Animations/StartPickupAnimNotify.h"
#include "Camera/CameraComponent.h"
#include "CentralObjects/Campfire.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameJam/GameJamGameModeBase.h"
#include "Kismet/GameplayStatics.h"

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
	
	PlayAnimMontage(PickupAnimMontage);

	SetCurrentBranches(currentBranches + 1);
	return true;
}

void AMainCharacter::PutAllBranches()
{
	PlayAnimMontage(PickupAnimMontage);

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), AddBranchesToCampfireSC, GetActorLocation());
	SetCurrentBranches(0);
}

void AMainCharacter::ExternalReloadTorch()
{
	if (currentLightSource)
	{
		currentLightSource->Repower();
	}
	else
	{
		AttachNewLightSource();
	}
}

ALightSource* AMainCharacter::GetCurrentLightSource()
{
	return currentLightSource;
}

void AMainCharacter::InternalReloadTorch()
{
	if (currentBranches == 0)
		return;
	
	SetCurrentBranches(currentBranches - 1);
	AttachNewLightSource();
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	currentBranches = 0;
	currentLightSource = nullptr;

	InitAnimations();
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
	if (!OnReload.ExecuteIfBound(this))
	{
		InternalReloadTorch();
	}
}

void AMainCharacter::AttachNewLightSource()
{
	if (!GetWorld() || !GetMesh())
		return;

	if (currentLightSource)
	{
		currentLightSource->Detach();
		currentLightSource->OnBurnOut.Unbind();
		currentLightSource = nullptr;
	}
	
	currentLightSource = GetWorld()->SpawnActor<ALightSource>(LightSourceClass);
	if (!currentLightSource)
		return;

	currentLightSource->SetOwner(this);
	FAttachmentTransformRules attachmentRules(EAttachmentRule::SnapToTarget, false);
	currentLightSource->AttachToComponent(GetMesh(), attachmentRules, LightSourceSocketName);

	currentLightSource->OnBurnOut.BindUObject(this, &AMainCharacter::OnTorchBurnOut);
}

void AMainCharacter::OnTorchBurnOut()
{
	currentLightSource->Detach();
	currentLightSource->OnBurnOut.Unbind();
	currentLightSource = nullptr;
}

void AMainCharacter::InitAnimations()
{
	if (!PickupAnimMontage)
		return;
	
	const auto NotifyEvents = PickupAnimMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents)
	{
		auto StartPickupNotify = Cast<UStartPickupAnimNotify>(NotifyEvent.Notify);
		if (StartPickupNotify)
		{
			StartPickupNotify->OnNotified.AddUObject(this, &AMainCharacter::StartPickupAnimation);
			continue;
		}

		auto EndPickupNotify = Cast<UEndPickupAnimNotify>(NotifyEvent.Notify);
		if (EndPickupNotify)
		{
			EndPickupNotify->OnNotified.AddUObject(this, &AMainCharacter::EndPickupAnimation);
			continue;
		}
	}
}

void AMainCharacter::StartPickupAnimation()
{
	const auto playerController = Cast<AMainPlayerController>(Controller);
	if (!playerController)
		return;

	playerController->DisableMovement();
}

void AMainCharacter::EndPickupAnimation()
{
	const auto playerController = Cast<AMainPlayerController>(Controller);
	if (!playerController)
		return;

	playerController->EnableMovement();
}

void AMainCharacter::SetCurrentBranches(int32 Amount)
{
	currentBranches = Amount;
	SetDecelerationMovement(currentBranches);
}

void AMainCharacter::SetDecelerationMovement(int32 Amount)
{
	if (!GetCharacterMovement())
		return;

	static float MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed - Amount * DecelerationMovementOneBranch;
}

bool AMainCharacter::InLight()
{
	TArray<AActor*> overlappingActors;
	GetOverlappingActors(overlappingActors, ACampfire::StaticClass());

	return overlappingActors.Num() != 0 || currentLightSource;
}
