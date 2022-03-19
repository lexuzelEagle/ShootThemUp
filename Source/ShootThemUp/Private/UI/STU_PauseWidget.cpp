// Shoot Them Up Game. All Rights Reserved


#include "UI/STU_PauseWidget.h"
#include "Gameframework/GameModeBase.h"
#include "Components/Button.h"

bool USTU_PauseWidget::Initialize()
{
	const auto InitStatus = Super::Initialize();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &USTU_PauseWidget::OnClearPause);
	}

	return InitStatus;
}

void USTU_PauseWidget::OnClearPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}