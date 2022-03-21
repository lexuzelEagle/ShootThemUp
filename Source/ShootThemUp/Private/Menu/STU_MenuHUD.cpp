// Shoot Them Up Game. All Rights Reserved


#include "Menu/STU_MenuHUD.h"
#include "Blueprint/UserWidget.h"

void ASTU_MenuHUD::BeginPlay()
{
	Super::BeginPlay();

	const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
	if (MenuWidget)
	{
		MenuWidget->AddToViewport();
	}
}
