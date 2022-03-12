// Shoot Them Up Game. All Rights Reserved


#include "AI/AICharacter.h"
#include "AI/STUAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/STU_AIWeaponComponent.h"
#include "BrainComponent.h"

AAICharacter::AAICharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USTU_AIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASTUAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

void AAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto STU_Controller = Cast<AAIController>(Controller);
	if (STU_Controller && STU_Controller->BrainComponent)
	{
		STU_Controller->BrainComponent->Cleanup();
	}
}
