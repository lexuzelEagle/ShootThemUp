// Shoot Them Up Game. All Rights Reserved


#include "AI/STUAIController.h"
#include "AI/AICharacter.h"
#include "AI/STUAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/STU_RespawnComponent.h"


ASTUAIController::ASTUAIController()
{
	STUAIPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>("STUAIPerceptionComponent");
	SetPerceptionComponent(*STUAIPerceptionComponent);

	RespawnComponent = CreateDefaultSubobject<USTU_RespawnComponent>("RespawnComponent");

	bWantsPlayerState = true;
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
	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}

AActor* ASTUAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
