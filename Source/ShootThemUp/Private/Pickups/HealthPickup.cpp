// Shoot Them Up Game. All Rights Reserved


#include "Pickups/HealthPickup.h"
#include "Player/STUHealthComponent.h"
#include "Dev/STUCoreUtils.h"


DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool AHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = Utils::GetComponent<USTUHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	UE_LOG(LogHealthPickup, Display, TEXT("Health was taken"));
	return HealthComponent->TryToAddHealth(HealthAmount);
}