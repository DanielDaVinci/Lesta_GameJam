// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FOnInteract, ACharacter*)
DECLARE_DELEGATE_OneParam(FOnReload, ACharacter*)

class ALightSource;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class GAMEJAM_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	FOnInteract OnInteract;
	FOnReload OnReload;
	
	AMainCharacter();

	UFUNCTION()
	bool AddBranch();

	int32 GetBranchesAmount() const { return currentBranches; };
	void PutAllBranches();
	
	void ReloadTorch();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Objects")
	TSubclassOf<ALightSource> LightSourceClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Objects")
	FName LightSourceSocketName = "TorchSocket";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	int32 MaxAmountBranches = 4;

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	int32 currentBranches = 0;
	
	void Interact();
	void Reload();

	void CreateLightSource();
};
