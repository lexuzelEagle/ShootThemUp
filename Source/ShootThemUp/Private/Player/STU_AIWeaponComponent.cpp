// Shoot Them Up Game. All Rights Reserved


#include "Player/STU_AIWeaponComponent.h"
#include "Weapons/STUBaseWeapon.h"

void USTU_AIWeaponComponent::FireStart()
{
	if (!CanFire()) return;
	if (CurrentWeapon->IsAmmoEmpty())
	{
		NextWeapon();
	}
	else
	{
		CurrentWeapon->FireStart();
	}
}

void USTU_AIWeaponComponent::NextWeapon()
{
	if (!CanEquip()) return;

	int32 NextIndex = (CurrentWeaponIdx + 1) % Weapons.Num();
	while (NextIndex != CurrentWeaponIdx)
	{
		if (!Weapons[NextIndex]->IsAmmoEmpty()) break;
		NextIndex = (NextIndex + 1) % Weapons.Num();
	}

	if (CurrentWeaponIdx != NextIndex)
	{
		CurrentWeaponIdx = NextIndex;
		EquipWeapon(CurrentWeaponIdx);
	}
}