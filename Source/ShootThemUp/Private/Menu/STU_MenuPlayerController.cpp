// Shoot Them Up Game. All Rights Reserved


#include "Menu/STU_MenuPlayerController.h"

void ASTU_MenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}