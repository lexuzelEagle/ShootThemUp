// Shoot Them Up Game. All Rights Reserved


#include "Player/WeaponComponent.h"
#include "Weapons/STUBaseWeapon.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
	
}

void UWeaponComponent::SpawnWeapon()
{
	check(GetWorld());

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	check(Character);

	CurrentWeapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
	check(CurrentWeapon);
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponSocket);
}

void UWeaponComponent::Fire()
{
	check(CurrentWeapon);

	CurrentWeapon->Fire();
}
