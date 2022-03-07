// Shoot Them Up Game. All Rights Reserved


#include "Weapons/STURifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "Weapons/WeaponFXComponent.h"

ASTURifleWeapon::ASTURifleWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<UWeaponFXComponent>("WeaponFXComponent");
}

void ASTURifleWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponFXComponent);
}

void ASTURifleWeapon::FireStart()
{
	Super::FireStart();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTURifleWeapon::MakeShot, TimeBetweenShots, true);
	MakeShot();
}

void ASTURifleWeapon::FireStop()
{
	Super::FireStop();
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASTURifleWeapon::MakeShot()
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

	const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);

	if (HitResult.bBlockingHit)
	{
		//DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), HitResult.ImpactPoint, FColor::Red, false, 5.0f, 0, 3.0f);
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Blue, false, 5.0f);
		WeaponFXComponent->PlayImpactFX(HitResult);

		DealDamage(HitResult);
	}
	else
	{
		DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, FColor::Red, false, 5.0f, 0, 3.0f);
	}

	DecreaseAmmo();
}

void ASTURifleWeapon::DealDamage(const FHitResult& HitResult)
{
	const auto Victim = HitResult.GetActor();
	check(Victim);

	Victim->TakeDamage(WeaponDamage, FDamageEvent(), nullptr, GetOwner());
}