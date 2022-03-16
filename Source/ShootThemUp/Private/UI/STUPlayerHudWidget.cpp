// Shoot Them Up Game. All Rights Reserved


#include "UI/STUPlayerHudWidget.h"
#include "Player/STUHealthComponent.h"
#include "Player/WeaponComponent.h"
#include "Dev/STUCoreUtils.h"
#include "STUGameModeBase.h"
#include "Player/STU_PlayerState.h"

float USTUPlayerHudWidget::GetHealthPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	const auto HealthComponent = Utils::GetComponent<USTUHealthComponent>(Player);
	if (!HealthComponent) return false;

	return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHudWidget::IsPlayerAlive() const
{
	const auto Player = GetOwningPlayerPawn();
	const auto HealthComponent = Utils::GetComponent<USTUHealthComponent>(Player);
	if (!HealthComponent) return false;

	return !HealthComponent->IsDead();
}

bool USTUPlayerHudWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	if (!Controller) return false;

	return Controller->GetStateName() == NAME_Spectating;
}

bool USTUPlayerHudWidget::Initialize()
{
	const auto HealthComponent = Utils::GetComponent<USTUHealthComponent>(GetOwningPlayerPawn());
	if (HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHudWidget::OnHealthChanged);
	}

	return Super::Initialize();
}

void USTUPlayerHudWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if (HealthDelta < 0.0f) OnTakeDamage();
}

bool USTUPlayerHudWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
	const auto Player = GetOwningPlayerPawn();
	const auto WeaponComponent = Utils::GetComponent<UWeaponComponent>(Player);
	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponUIData(UIData);
}

bool USTUPlayerHudWidget::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto Player = GetOwningPlayerPawn();
	const auto WeaponComponent = Utils::GetComponent<UWeaponComponent>(Player);
	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponAmmoData(AmmoData);
}

int32 USTUPlayerHudWidget::GetKillsNum() const
{
	const auto PlayerState = GetPlayerState();
	return PlayerState ? PlayerState->GetKillsNum() : -1;
}

int32 USTUPlayerHudWidget::GetDeathsNum() const
{
	const auto PlayerState = GetPlayerState();
	return PlayerState ? PlayerState->GetDeathsNum() : -1;
}

int32 USTUPlayerHudWidget::GetCurrentRoundNum() const
{
	const auto GameMode = GetGameMode();
	return GameMode ? GameMode->GetCurrentRound() : -1;
}

int32 USTUPlayerHudWidget::GetTotalRoundsNum() const
{
	const auto GameMode = GetGameMode();
	return GameMode ? GameMode->GetGameData().RoundsNum : -1;
}

int32 USTUPlayerHudWidget::GetRoundSecondsRemaining() const
{
	const auto GameMode = GetGameMode();
	return GameMode ? GameMode->GetRoundCountDown() : -1;
}

ASTUGameModeBase* USTUPlayerHudWidget::GetGameMode() const
{
	return GetWorld() ? Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASTU_PlayerState* USTUPlayerHudWidget::GetPlayerState() const
{
	return GetOwningPlayer() ? Cast<ASTU_PlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
