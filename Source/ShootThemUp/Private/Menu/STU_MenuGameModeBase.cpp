// Shoot Them Up Game. All Rights Reserved


#include "Menu/STU_MenuGameModeBase.h"
#include "Menu/STU_MenuPlayerController.h"
#include "Menu/STU_MenuHUD.h"


ASTU_MenuGameModeBase::ASTU_MenuGameModeBase()
{
	PlayerControllerClass = ASTU_MenuPlayerController::StaticClass();
	HUDClass = ASTU_MenuHUD::StaticClass();
}