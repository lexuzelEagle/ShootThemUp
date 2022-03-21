// Shoot Them Up Game. All Rights Reserved


#include "UI/STU_PauseWidget.h"
#include "Gameframework/GameModeBase.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STU_GameInstance.h"

void USTU_PauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &USTU_PauseWidget::OnClearPause);
	}

	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &USTU_PauseWidget::OnMainMenu);
	}
}

void USTU_PauseWidget::OnClearPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}

void USTU_PauseWidget::OnMainMenu()
{
	if (!GetWorld()) return;

	const auto STUGameInstance = GetWorld()->GetGameInstance<USTU_GameInstance>();
	if (!STUGameInstance) return;

	const auto MenuLevelName = STUGameInstance->GetMenuLevelName();
	if (MenuLevelName.IsNone()) return;

	UGameplayStatics::OpenLevel(GetWorld(), MenuLevelName);
}
