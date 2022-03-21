// Shoot Them Up Game. All Rights Reserved


#include "Menu/STU_MenuPlayerController.h"
#include "STU_GameInstance.h"

void ASTU_MenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}