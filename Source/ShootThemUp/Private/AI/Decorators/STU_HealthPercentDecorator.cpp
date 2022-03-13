// Shoot Them Up Game. All Rights Reserved


#include "AI/Decorators/STU_HealthPercentDecorator.h"
#include "AIController.h"
#include "Dev/STUCoreUtils.h"
#include "Player/STUHealthComponent.h"



USTU_HealthPercentDecorator::USTU_HealthPercentDecorator()
{
	NodeName = "Health Percent";
}

bool USTU_HealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto HealthComponent = Utils::GetComponent<USTUHealthComponent>(Controller->GetPawn());
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->GetHealthPercent() < HealthPercent;
}
