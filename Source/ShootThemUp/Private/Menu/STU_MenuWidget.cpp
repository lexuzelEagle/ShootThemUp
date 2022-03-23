// Shoot Them Up Game. All Rights Reserved


#include "Menu/STU_MenuWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "STU_GameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Menu/STU_LevelItemWidget.h"


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

	InitLevelItems();
}

void USTU_MenuWidget::OnStartGame()
{
	const auto STUGameInstance = GetSTUGameInstance();
	if (!STUGameInstance) return;

	const auto StartupLevelName = STUGameInstance->GetStartupLevel().LevelName;
	UGameplayStatics::OpenLevel(GetWorld(), StartupLevelName);
}

void USTU_MenuWidget::OnQuitGame()
{
	if (!GetWorld() || !GetOwningPlayer()) return;

	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USTU_MenuWidget::InitLevelItems()
{
	const auto STUGameInstance = GetSTUGameInstance();
	if (!STUGameInstance) return;

	checkf(STUGameInstance->GetLevelData().Num() != 0, TEXT("Levels data must not be empty!"));

	if (!LevelItemsBox) return;
	LevelItemsBox->ClearChildren();

	for (auto LevelData : STUGameInstance->GetLevelData())
	{
		const auto LevelItemWidget = CreateWidget<USTU_LevelItemWidget>(GetWorld(), LevelItemWidgetClass);
		if (!LevelItemWidget) continue;

		LevelItemWidget->SetLevelData(LevelData);
		LevelItemWidget->OnLevelSelected.AddUObject(this, &USTU_MenuWidget::OnLevelSelected);

		LevelItemsBox->AddChild(LevelItemWidget);
		LevelItemWidgets.Add(LevelItemWidget);
	}

	if (STUGameInstance->GetStartupLevel().LevelName.IsNone())
	{
		OnLevelSelected(STUGameInstance->GetLevelData()[0]);
	}
	else
	{
		OnLevelSelected(STUGameInstance->GetStartupLevel());
	}
}

void USTU_MenuWidget::OnLevelSelected(const FLevelData& Data)
{
	const auto STUGameInstance = GetSTUGameInstance();
	if (!STUGameInstance) return;

	STUGameInstance->SetStartupLevel(Data);

	for (auto LevelItemWidget : LevelItemWidgets)
	{
		if (LevelItemWidget)
		{
			const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
			LevelItemWidget->SetSelected(IsSelected);
		}
	}
}

USTU_GameInstance* USTU_MenuWidget::GetSTUGameInstance() const
{
	if (!GetWorld()) return nullptr;
	return GetWorld()->GetGameInstance<USTU_GameInstance>();
}
