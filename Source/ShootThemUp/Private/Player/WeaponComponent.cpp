// Shoot Them Up Game. All Rights Reserved


#include "Player/WeaponComponent.h"
#include "Weapons/STUBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Player/STUBaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)

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

	Character = Cast<ASTUBaseCharacter>(GetOwner());
	check(Character);

	SpawnWeapon();
	
}

void UWeaponComponent::SpawnWeapon()
{
	check(GetWorld());

	CurrentWeapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
	check(CurrentWeapon);
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponSocket);
	CurrentWeapon->SetOwner(Character);
}

void UWeaponComponent::FireStart()
{
	UE_LOG(LogWeaponComponent, Display, TEXT("Fire!!!"));
	if (Character->IsRunning()) return;
	UE_LOG(LogWeaponComponent, Display, TEXT("IsNotRunning"));

	check(CurrentWeapon);

	CurrentWeapon->FireStart();
}

void UWeaponComponent::FireStop()
{
	check(CurrentWeapon);
	CurrentWeapon->FireStop();
}
