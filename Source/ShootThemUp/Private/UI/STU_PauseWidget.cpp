// Shoot Them Up Game. All Rights Reserved


#include "UI/STU_PauseWidget.h"
#include "Gameframework/GameModeBase.h"
#include "Components/Button.h"

void USTU_PauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &USTU_PauseWidget::OnClearPause);
	}
}

void USTU_PauseWidget::OnClearPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}