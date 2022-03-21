// Shoot Them Up Game. All Rights Reserved


#include "Menu/STU_MenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STU_GameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogMenuWidget, All, All);

void USTU_MenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &USTU_MenuWidget::OnStartGame);
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
