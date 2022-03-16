// Shoot Them Up Game. All Rights Reserved


#include "Player/STU_PlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUPlayerState, All, All)

void ASTU_PlayerState::LogInfo()
{
	UE_LOG(LogSTUPlayerState, Display, TEXT("TeamID = %i; Kills = %i; Deaths = %i"), TeamID, KillsNum, DeathsNum);
}
