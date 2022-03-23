// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Dev/STUCoreUtils.h"
#include "STU_MenuWidget.generated.h"


class UButton;
class UHorizontalBox;
class USTU_GameInstance;
class USTU_LevelItemWidget;

UCLASS()
class SHOOTTHEMUP_API USTU_MenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
		UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
		UHorizontalBox* LevelItemsBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<USTU_LevelItemWidget> LevelItemWidgetClass;

	virtual void NativeOnInitialized() override;

private:
	UPROPERTY()
		TArray<USTU_LevelItemWidget*> LevelItemWidgets;

	UFUNCTION()
		void OnStartGame();

	UFUNCTION()
		void OnQuitGame();

	void InitLevelItems();
	void OnLevelSelected(const FLevelData& Data);
	USTU_GameInstance* GetSTUGameInstance() const;
	
};
