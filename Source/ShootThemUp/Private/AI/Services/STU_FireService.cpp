// Shoot Them Up Game. All Rights Reserved


#include "AI/Services/STU_FireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Dev/STUCoreUtils.h"
#include "Player/WeaponComponent.h"

USTU_FireService::USTU_FireService()
{
	NodeName = "Fire";
}

void USTU_FireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if (Controller)
	{
		const auto WeaponComponent = Utils::GetComponent<UWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent)
		{
			HasAim ? WeaponComponent->FireStart() : WeaponComponent->FireStop();
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
