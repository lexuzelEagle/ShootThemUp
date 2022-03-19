// Shoot Them Up Game. All Rights Reserved


#include "UI/STU_GameOverWidget.h"
#include "STUGameModeBase.h"
#include "Player/STU_PlayerState.h"
#include "UI/STU_PlayerStatRowWidget.h"
#include "Components/VerticalBox.h"


bool USTU_GameOverWidget::Initialize()
{
	if (GetWorld())
	{
		const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &USTU_GameOverWidget::OnMatchStateChanged);
		}
	}

	return Super::Initialize();
}

void USTU_GameOverWidget::OnMatchStateChanged(ESTU_MatchState State)
{
	if (State == ESTU_MatchState::GameOver)
	{
		UpdatePlayerStat();
	}
}


void USTU_GameOverWidget::UpdatePlayerStat()
{
	if (!GetWorld() || !PlayerStatBox) return;

	PlayerStatBox->ClearChildren();

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<ASTU_PlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		const auto PlayerStatRowWidget = CreateWidget<USTU_PlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
		if (!PlayerStatRowWidget) continue;

		PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
		PlayerStatRowWidget->SetKills(Utils::TextFromInt(PlayerState->GetKillsNum()));
		PlayerStatRowWidget->SetDeaths(Utils::TextFromInt(PlayerState->GetDeathsNum()));
		PlayerStatRowWidget->SetTeam(Utils::TextFromInt(PlayerState->GetTeamID()));
		PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());

		PlayerStatBox->AddChild(PlayerStatRowWidget);
	}
}