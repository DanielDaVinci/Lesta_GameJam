// Lesta GameJam, Lazy Pixel. All Rights Reserved


#include "Menu/UI/MenuHUD.h"

#include "Blueprint/UserWidget.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MenuWidgetClass)
	{
		const auto menuWidget = CreateWidget(GetWorld(), MenuWidgetClass);
		if (menuWidget)
			menuWidget->AddToViewport();
	}
}
