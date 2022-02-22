// Shoot Them Up Game. All Rights Reserved


#include "UI/STUPlayerHudWidget.h"
#include "Player/STUHealthComponent.h"

float USTUPlayerHudWidget::GetHealthPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return 0.0;

	const auto Component = Player->GetComponentByClass(USTUHealthComponent::StaticClass());
	const auto HealthComponent = Cast< USTUHealthComponent>(Component);
	if (!HealthComponent) return 0.0;

	return HealthComponent->GetHealthPercent();
}