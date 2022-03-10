// Shoot Them Up Game. All Rights Reserved


#include "AI/STUAIController.h"
#include "AI/AICharacter.h"


void ASTUAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto STUCharacter = Cast<AAICharacter>(InPawn);
	if (STUCharacter)
	{
		RunBehaviorTree(STUCharacter->BehaviorTreeAsset);
	}
}