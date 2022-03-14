// Shoot Them Up Game. All Rights Reserved


#include "AI/Decorators/STU_NeedAmmoDecorator.h"
#include "AIController.h"
#include "Dev/STUCoreUtils.h"
#include "Player/WeaponComponent.h"



USTU_NeedAmmoDecorator::USTU_NeedAmmoDecorator()
{
	NodeName = "Need Ammo";
}

bool USTU_NeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto WeaponComponent = Utils::GetComponent<UWeaponComponent>(Controller->GetPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->NeedAmmo(WeaponType);
}
