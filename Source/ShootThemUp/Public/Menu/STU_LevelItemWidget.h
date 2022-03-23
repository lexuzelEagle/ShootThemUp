// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Dev/STUCoreUtils.h"
#include "STU_LevelItemWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;

UCLASS()
class SHOOTTHEMUP_API USTU_LevelItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FOnLevelSelecetedSignature OnLevelSelected;

	void SetLevelData(const FLevelData& Data);
	FLevelData GetLevelData() const { return LevelData; }

	void SetSelected(bool IsSelected);

protected:
	UPROPERTY(meta = (BindWidget))
		UButton* LevelSelectButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* LevelNameTextBlock;

	UPROPERTY(meta = (BindWidget))
		UImage* LevelImage;

	UPROPERTY(meta = (BindWidget))
		UImage* FrameImage;

	virtual void NativeOnInitialized() override;

private:
	FLevelData LevelData;

	UFUNCTION()
		void OnLevelItemClicked();
};
