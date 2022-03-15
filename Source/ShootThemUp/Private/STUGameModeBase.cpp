// Shoot Them Up Game. All Rights Reserved


#include "STUGameModeBase.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "AIController.h"
#include "UI/STUHUD.h"


ASTUGameModeBase::ASTUGameModeBase()
{
	DefaultPawnClass = ASTUBaseCharacter::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
	HUDClass = ASTUHUD::StaticClass();
}

void ASTUGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
}

void ASTUGameModeBase::SpawnBots()
{
	if (!GetWorld()) return;

	for (int32 i = 0; i < GameData.PlayersNum - 1; i++)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto STU_AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(STU_AIController);
	}
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}
