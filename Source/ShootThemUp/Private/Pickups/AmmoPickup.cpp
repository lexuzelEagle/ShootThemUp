// Shoot Them Up Game. All Rights Reserved


#include "Pickups/AmmoPickup.h"
#include "Player/STUHealthComponent.h"
#include "Player/WeaponComponent.h"
#include "Dev/STUCoreUtils.h"


DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool AAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = Utils::GetComponent<USTUHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	const auto WeaponComponent = Utils::GetComponent<UWeaponComponent>(PlayerPawn);
	if (!WeaponComponent) return false;

	UE_LOG(LogAmmoPickup, Display, TEXT("Ammo was taken"));
	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}