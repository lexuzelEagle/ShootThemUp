// Shoot Them Up Game. All Rights Reserved


#include "Player/STU_RespawnComponent.h"
#include "STUGameModeBase.h"


USTU_RespawnComponent::USTU_RespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void USTU_RespawnComponent::Respawn(int32 RespawnTime)
{
	if (!GetWorld()) return;

	RespawnCountDown = RespawnTime;
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &USTU_RespawnComponent::UpdateTimer, 1.0f, true);
}

void USTU_RespawnComponent::UpdateTimer()
{
	if (--RespawnCountDown == 0)
	{
		if (!GetWorld()) return;

		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);
		const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
		if (!GameMode) return;

		GameMode->RespawnRequest(Cast<AController>(GetOwner()));
	}
}
