// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapons/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"


UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void FireStart() override;
	virtual void FireStop() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float TimeBetweenShots = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float WeaponDamage = 2.0f;

	virtual void MakeShot() override;
	void DealDamage(const FHitResult& HitResult);

private:
	FTimerHandle ShotTimerHandle;
};
