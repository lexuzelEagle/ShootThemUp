// Shoot Them Up Game. All Rights Reserved


#include "Player/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Dev/FireDamageType.h"
#include "Dev/IceDamageType.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	check(ComponentOwner);
	ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeDamage);
}

void USTUHealthComponent::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	SetHealth(Health - Damage);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}

	UE_LOG(LogHealthComponent, Display, TEXT("Taken Damage = %.1f"), Damage);

	if (DamageType)
	{
		if (DamageType->IsA<UFireDamageType>())
		{
			UE_LOG(LogHealthComponent, Display, TEXT("FIRE FIRE FIRE"));
		}
		else if (DamageType->IsA<UIceDamageType>())
		{
			UE_LOG(LogHealthComponent, Display, TEXT("ICE ICE ICE"));
		}
	}
}

void USTUHealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);

	if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}

