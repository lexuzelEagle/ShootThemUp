// Shoot Them Up Game. All Rights Reserved


#include "Menu/STU_MenuHUD.h"
#include "UI/STU_BaseWidget.h"

void ASTU_MenuHUD::BeginPlay()
{
	Super::BeginPlay();

	const auto MenuWidget = CreateWidget<USTU_BaseWidget>(GetWorld(), MenuWidgetClass);
	if (MenuWidget)
	{
		MenuWidget->AddToViewport();
		MenuWidget->Show();
	}
}
