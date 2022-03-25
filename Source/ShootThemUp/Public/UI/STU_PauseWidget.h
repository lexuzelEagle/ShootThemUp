// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/STU_BaseWidget.h"
#include "STU_PauseWidget.generated.h"

class UButton;

UCLASS()
class SHOOTTHEMUP_API USTU_PauseWidget : public USTU_BaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		UButton* ClearPauseButton;

	UPROPERTY(meta = (BindWidget))
		UButton* MainMenuButton;

	virtual void NativeOnInitialized() override;
private:
	UFUNCTION()
		void OnClearPause();

	UFUNCTION()
		void OnMainMenu();
};
