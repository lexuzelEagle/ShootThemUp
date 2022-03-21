// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STU_MenuWidget.generated.h"


class UButton;

UCLASS()
class SHOOTTHEMUP_API USTU_MenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
		UButton* QuitGameButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
		void OnStartGame();

	UFUNCTION()
		void OnQuitGame();
	
};
