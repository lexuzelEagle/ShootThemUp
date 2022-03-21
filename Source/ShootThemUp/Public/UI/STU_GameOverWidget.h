// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Dev/STUCoreUtils.h"
#include "STU_GameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class SHOOTTHEMUP_API USTU_GameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* PlayerStatBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

	UPROPERTY(meta = (BindWidget))
		UButton* ResetLvlButton;

	UPROPERTY(meta = (BindWidget))
		UButton* MainMenuButton;

	virtual void NativeOnInitialized() override;
private:
	void OnMatchStateChanged(ESTU_MatchState State);
	void UpdatePlayerStat();

	UFUNCTION()
		void OnResetLvl();

	UFUNCTION()
		void OnMainMenu();
};
