// Shoot Them Up Game. All Rights Reserved


#include "AI/STUAIPerceptionComponent.h"
#include "AIController.h"
#include "Dev/STUCoreUtils.h"
#include "Player/STUHealthComponent.h"
#include "Perception/AISense_Sight.h"



AActor* USTUAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PerceivedActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);
	if (PerceivedActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for (const auto PerceivedActor : PerceivedActors)
	{
		const auto HealthComponent = Utils::GetComponent<USTUHealthComponent>(PerceivedActor);
		const auto PerceivedPawn = Cast<APawn>(PerceivedActor);
		const auto AreEnemies = PerceivedPawn && Utils::AreEnemies(Controller, PerceivedPawn->GetController());

		if (HealthComponent && !HealthComponent->IsDead() && AreEnemies)
		{
			const auto CurrentDistance = (PerceivedActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PerceivedActor;
			}
		}
	}

	return BestPawn;
}