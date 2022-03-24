// Shoot Them Up Game. All Rights Reserved


#include "UI/STU_PlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void USTU_PlayerStatRowWidget::SetPlayerName(const FText& Text)
{
	if (!PlayerNameTextBlock) return;
	PlayerNameTextBlock->SetText(Text);
}


void USTU_PlayerStatRowWidget::SetKills(const FText& Text)
{
	if (!KillsTextBlock) return;
	KillsTextBlock->SetText(Text);
}


void USTU_PlayerStatRowWidget::SetDeaths(const FText& Text)
{
	if (!DeathsTextBlock) return;
	DeathsTextBlock->SetText(Text);
}


void USTU_PlayerStatRowWidget::SetTeam(const FText& Text)
{
	if (!TeamTextBlock) return;
	TeamTextBlock->SetText(Text);
}


void USTU_PlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
	if (!PlayerIndicatorImage) return;
	PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USTU_PlayerStatRowWidget::SetTeamColor(const FLinearColor& Color)
{
	if (!TeamColorImage) return;

	TeamColorImage->SetColorAndOpacity(Color);
}