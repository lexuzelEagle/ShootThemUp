// Shoot Them Up Game. All Rights Reserved


#include "UI/STUPlayerHudWidget.h"
#include "Player/STUHealthComponent.h"
#include "Player/WeaponComponent.h"

float USTUPlayerHudWidget::GetHealthPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return 0.0f;

	const auto Component = Player->GetComponentByClass(USTUHealthComponent::StaticClass());
	const auto HealthComponent = Cast<USTUHealthComponent>(Component);
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHudWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = GetWeaponComponent();
	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponUIData(UIData);
}

bool USTUPlayerHudWidget::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = GetWeaponComponent();
	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponAmmoData(AmmoData);
}

UWeaponComponent* USTUPlayerHudWidget::GetWeaponComponent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return nullptr;

	const auto Component = Player->GetComponentByClass(UWeaponComponent::StaticClass());
	const auto WeaponComponent = Cast<UWeaponComponent>(Component);
	return WeaponComponent;
}
