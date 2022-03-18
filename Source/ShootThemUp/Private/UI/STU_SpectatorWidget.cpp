// Shoot Them Up Game. All Rights Reserved


#include "UI/STU_SpectatorWidget.h"
#include "Dev/STUCoreUtils.h"
#include "Player/STU_RespawnComponent.h"

bool USTU_SpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
	const auto RespawnComponent = Utils::GetComponent<USTU_RespawnComponent>(GetOwningPlayer());
	if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

	CountDownTime = RespawnComponent->GetRespawnCountDown();
	return true;
}