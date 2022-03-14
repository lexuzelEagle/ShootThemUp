// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STU_NeedAmmoDecorator.generated.h"

class ASTUBaseWeapon;

UCLASS()
class SHOOTTHEMUP_API USTU_NeedAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	USTU_NeedAmmoDecorator();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<ASTUBaseWeapon> WeaponType;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
