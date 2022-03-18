// Shoot Them Up Game. All Rights Reserved


#include "Player/STUPlayerController.h"
#include "Player/STU_RespawnComponent.h"


ASTUPlayerController::ASTUPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USTU_RespawnComponent>("RespawnComponent");
}

void ASTUPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OnNewPawn.Broadcast(InPawn);
}
