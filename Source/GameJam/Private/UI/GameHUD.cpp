// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameHUD.h"

#include "Blueprint/UserWidget.h"

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	const auto playerWidget = CreateWidget(GetWorld(), PlayerWidgetClass);
	if (playerWidget)
		playerWidget->AddToViewport();
	
}
