// Shoot Them Up Game. All Rights Reserved


#include "Menu/STU_MenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

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
	const FName StartupLevelName = "TestLevel";
	UGameplayStatics::OpenLevel(this, StartupLevelName);
}
