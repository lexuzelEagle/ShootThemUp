// Shoot Them Up Game. All Rights Reserved


#include "Player/WeaponComponent.h"
#include "Weapons/STUBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Player/STUBaseCharacter.h"
#include "Animations/STUEquipFinishedAnimNotify.h"

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

	InitAnimations();

	Character = Cast<ASTUBaseCharacter>(GetOwner());
	check(Character);
	
	CurrentWeaponIdx = 0;

	SpawnWeapons();
	EquipWeapon(CurrentWeaponIdx);
}

void UWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;

	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();

	Super::EndPlay(EndPlayReason);
}

void UWeaponComponent::SpawnWeapons()
{
	check(GetWorld());

	for (auto OneWeaponData : WeaponData)
	{
		auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(OneWeaponData.WeaponClass);
		check(Weapon);
		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, WeaponArmorySocket);
	}
}

void UWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* Weapon, const FName& SocketName)
{
	check(Weapon);
	check(Character);
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, SocketName);
}

void UWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if (!CanEquip() || WeaponIndex < 0 || WeaponIndex >= Weapons.Num()) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->FireStop();
		AttachWeaponToSocket(CurrentWeapon, WeaponArmorySocket);
	}

	CurrentWeapon = Weapons[WeaponIndex];

	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data) 
		{ 
			return Data.WeaponClass == CurrentWeapon->GetClass(); 
		});
	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

	AttachWeaponToSocket(CurrentWeapon, WeaponEquipSocket);
	EquipAnimationInProgress = true;
	PlayAnimMontage(EquipAnimMontage);
}

void UWeaponComponent::InitAnimations()
{
	check(EquipAnimMontage);

	const auto NotifyEvents = EquipAnimMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents)
	{
		auto EquipFinishedNotify = Cast<USTUEquipFinishedAnimNotify>(NotifyEvent.Notify);
		if (EquipFinishedNotify)
		{
			EquipFinishedNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnEquipFinished);
			break;
		}
	}
}

void UWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	if (Character->GetMesh() == MeshComponent)
	{
		EquipAnimationInProgress = false;
		UE_LOG(LogWeaponComponent, Display, TEXT("Equip finished!"));
	}
}

void UWeaponComponent::FireStart()
{
	if (!CanFire()) return;

	CurrentWeapon->FireStart();
}

void UWeaponComponent::FireStop()
{
	check(CurrentWeapon);
	CurrentWeapon->FireStop();
}

void UWeaponComponent::NextWeapon()
{
	CurrentWeaponIdx = (CurrentWeaponIdx + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIdx);
}

void UWeaponComponent::Reload()
{
	PlayAnimMontage(CurrentReloadAnimMontage);
}

void UWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	check(Character);
	Character->PlayAnimMontage(Animation);
}

bool UWeaponComponent::CanFire()
{ 
	check(Character);
	return CurrentWeapon && !EquipAnimationInProgress && !ReloadAnimationInProgress && !Character->IsRunning();
}
