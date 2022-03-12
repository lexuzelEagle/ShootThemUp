// Shoot Them Up Game. All Rights Reserved


#include "AI/Services/STU_ChangeWeaponService.h"
#include "AIController.h"
#include "Dev/STUCoreUtils.h"
#include "Player/WeaponComponent.h"

USTU_ChangeWeaponService::USTU_ChangeWeaponService()
{
	NodeName = "ChangeWeapon";
}

void USTU_ChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (Controller)
	{
		const auto WeaponComponent = Utils::GetComponent<UWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
		{
			WeaponComponent->NextWeapon();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}