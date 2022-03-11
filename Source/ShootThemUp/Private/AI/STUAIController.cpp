// Shoot Them Up Game. All Rights Reserved


#include "AI/STUAIController.h"
#include "AI/AICharacter.h"
#include "AI/STUAIPerceptionComponent.h"


ASTUAIController::ASTUAIController()
{
	STUAIPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>("Perception Component");
	SetPerceptionComponent(*STUAIPerceptionComponent);
}

void ASTUAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto STUCharacter = Cast<AAICharacter>(InPawn);
	if (STUCharacter)
	{
		RunBehaviorTree(STUCharacter->BehaviorTreeAsset);
	}
}

void ASTUAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto AimActor = STUAIPerceptionComponent->GetClosestEnemy();
	SetFocus(AimActor);
}