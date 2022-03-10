// Shoot Them Up Game. All Rights Reserved


#include "AI/AICharacter.h"
#include "AI/STUAIController.h"

AAICharacter::AAICharacter(const FObjectInitializer& ObjInit)
{
	Super(ObjInit);
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASTUAIController::StaticClass();
}