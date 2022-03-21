// Shoot Them Up Game. All Rights Reserved


#include "Menu/STU_MenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STU_GameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogMenuWidget, All, All);

void USTU_MenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &USTU_MenuWidget::OnStartGame);
	}

	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &USTU_MenuWidget::OnQuitGame);
	}
}

void USTU_MenuWidget::OnStartGame()
{
	if (!GetWorld()) return;

	const auto STUGameInstance = GetWorld()->GetGameInstance<USTU_GameInstance>();
	if (!STUGameInstance) return;

	const auto StartupLevelName = STUGameInstance->GetStartupLevelName();
	if (StartupLevelName.IsNone())
	{
		UE_LOG(LogMenuWidget, Error, TEXT("Startup level is NONE!"));
		return;
	}

	UGameplayStatics::OpenLevel(GetWorld(), StartupLevelName);
}

void USTU_MenuWidget::OnQuitGame()
{
	if (!GetWorld() || !GetOwningPlayer()) return;

	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}
