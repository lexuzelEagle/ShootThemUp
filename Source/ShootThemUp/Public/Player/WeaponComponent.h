// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "Dev/STUCoreUtils.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ASTUBaseWeapon;
class ASTUBaseCharacter;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

	virtual void FireStart();
	void FireStop();
	virtual void NextWeapon();
	void Reload();

	bool GetWeaponUIData(FWeaponUIData& UIData) const;
	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;

	bool TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType, int32 ClipsAmount);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		FName WeaponEquipSocket = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		FName WeaponArmorySocket = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UAnimMontage* EquipAnimMontage;

	UPROPERTY()
		ASTUBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
		TArray<ASTUBaseWeapon*> Weapons;
	
	int32 CurrentWeaponIdx = 0;

	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	bool CanFire() const;
	bool CanEquip() const;
	void EquipWeapon(int32 WeaponIndex);

private:		
	UPROPERTY()
		UAnimMontage* CurrentReloadAnimMontage = nullptr;

	UPROPERTY()
		ASTUBaseCharacter* Character = nullptr;

	bool EquipAnimationInProgress = false;
	bool ReloadAnimationInProgress = false;

	void SpawnWeapons();
	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, const FName& SocketName);

	void PlayAnimMontage(UAnimMontage* Animation);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	bool CanReload() const;

	void OnEmptyClip();
	void ChangeClip();
};
