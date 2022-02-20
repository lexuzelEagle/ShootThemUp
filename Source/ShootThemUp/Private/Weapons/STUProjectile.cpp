// Shoot Them Up Game. All Rights Reserved


#include "Weapons/STUProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProkectileMovementComponent");
	MovementComponent->InitialSpeed = 2000.0f;
}

void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	check(CollisionComponent);
	check(MovementComponent);
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);
	SetLifeSpan(LifeTime);
}

void ASTUProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	check(GetWorld());

	MovementComponent->StopMovementImmediately();

	// make damage
	UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(), DamageRadius, 
		UDamageType::StaticClass(), {GetOwner()}, this, nullptr, DoFullDamage);

	DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Blue, false, 5.0f);

	Destroy();
}

AController* ASTUProjectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}

