// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapons/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void FireStart() override;
	virtual void FireStop() override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float TimeBetweenShots = 0.1f;

	virtual void MakeShot() override;
	virtual void DealDamage(const FHitResult& HitResult) override;

private:
	FTimerHandle ShotTimerHandle;
};
