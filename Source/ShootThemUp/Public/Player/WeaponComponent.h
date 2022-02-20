// Shoot Them Up Game. All Rights Reserved

#pragma once

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

	void FireStart();
	void FireStop();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<ASTUBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		FName WeaponSocket = "WeaponSocket";

	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	UPROPERTY()
		ASTUBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
		ASTUBaseCharacter* Character = nullptr;

	void SpawnWeapon();
};
