// Shoot Them Up Game. All Rights Reserved


#include "Weapons/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh);
}

void ASTUBaseWeapon::Fire()
{
	UE_LOG(LogBaseWeapon, Display, TEXT("Fire!"));
	MakeShot();
}

void ASTUBaseWeapon::MakeShot()
{
	check(GetWorld());

	const auto Player = Cast<ACharacter>(GetOwner());
	check(Player);

	const auto Controller = Player->GetController<APlayerController>();
	check(Controller);

	FVector ViewLocation;
	FRotator ViewRotation;
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);

//	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector TraceStart = ViewLocation;

//	const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();
	const FVector ShootDirection = ViewRotation.Vector();

	const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

//	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 5.0f, 0, 3.0f);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);

	if (HitResult.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), HitResult.ImpactPoint, FColor::Red, false, 5.0f, 0, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Blue, false, 5.0f);

		UE_LOG(LogBaseWeapon, Display, TEXT("Bone = %s"), *HitResult.BoneName.ToString());

		DealDamage(HitResult);
	}
	else
	{
		DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, FColor::Red, false, 5.0f, 0, 3.0f);
	}
}

void ASTUBaseWeapon::DealDamage(const FHitResult& HitResult)
{
	const auto Victim = HitResult.GetActor();
	check(Victim);

	Victim->TakeDamage(WeaponDamage, FDamageEvent(), nullptr, GetOwner());
	UE_LOG(LogBaseWeapon, Display, TEXT("%s caused %f Damage to %s"), *GetOwner()->GetHumanReadableName(), WeaponDamage, *Victim->GetHumanReadableName());
}