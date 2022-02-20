// Shoot Them Up Game. All Rights Reserved


#include "Weapons/STULauncherWeapon.h"
#include "Weapons/STUProjectile.h"
#include "Kismet/GameplayStatics.h"

void ASTULauncherWeapon::FireStart()
{
	Super::FireStart();

	MakeShot();
}

void ASTULauncherWeapon::FireStop()
{
	Super::FireStop();
}

void ASTULauncherWeapon::MakeShot()
{
	const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);

	const FTransform SpawnTransform(FRotator::ZeroRotator, SocketTransform.GetLocation());
	AActor* Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);
	// set projectile params

	UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
}

void ASTULauncherWeapon::DealDamage(const FHitResult& HitResult)
{
	Super::DealDamage(HitResult);

	const auto Victim = HitResult.GetActor();
	check(Victim);

	Victim->TakeDamage(WeaponDamage, FDamageEvent(), nullptr, GetOwner());
}