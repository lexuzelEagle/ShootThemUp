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
	Super::MakeShot();
	check(GetWorld());

	if (IsAmmoEmpty())
	{
		FireStop();
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);

	const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - SocketTransform.GetLocation()).GetSafeNormal();

	const FTransform SpawnTransform(FRotator::ZeroRotator, SocketTransform.GetLocation());
	ASTUProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform);
	check(Projectile);
	Projectile->SetShotDirection(Direction);
	Projectile->SetOwner(GetOwner());
	Projectile->FinishSpawning(SpawnTransform);

	DecreaseAmmo();
	SpawnMuzzleFX();
}