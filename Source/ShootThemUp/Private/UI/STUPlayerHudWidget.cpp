// Shoot Them Up Game. All Rights Reserved


#include "UI/STUPlayerHudWidget.h"
#include "Player/STUHealthComponent.h"
#include "Player/WeaponComponent.h"
#include "Dev/STUCoreUtils.h"

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
