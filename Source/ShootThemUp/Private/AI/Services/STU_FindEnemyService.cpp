// Shoot Them Up Game. All Rights Reserved


#include "AI/Services/STU_FindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Dev/STUCoreUtils.h"
#include "AI/STUAIPerceptionComponent.h"

USTU_FindEnemyService::USTU_FindEnemyService()
{
	NodeName = "Find Enemy";
}

void USTU_FindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = Utils::GetComponent<USTUAIPerceptionComponent>(Controller);
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}