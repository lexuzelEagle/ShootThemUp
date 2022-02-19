// Shoot Them Up Game. All Rights Reserved


#include "Weapons/STURifleWeapon.h"

void ASTURifleWeapon::FireStart()
{
	Super::FireStart();

	MakeShot();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTURifleWeapon::MakeShot, TimeBetweenShots, true);
}

void ASTURifleWeapon::FireStop()
{
	Super::FireStop();
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASTURifleWeapon::MakeShot()
{
	Super::MakeShot();
}

void ASTURifleWeapon::DealDamage(const FHitResult& HitResult)
{
	Super::DealDamage(HitResult);

	const auto Victim = HitResult.GetActor();
	check(Victim);

	Victim->TakeDamage(WeaponDamage, FDamageEvent(), nullptr, GetOwner());
}