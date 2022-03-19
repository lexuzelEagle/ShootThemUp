// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Dev/STUCoreUtils.h"
#include "STU_GameOverWidget.generated.h"

class UVerticalBox;

UCLASS()
class SHOOTTHEMUP_API USTU_GameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* PlayerStatBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

private:
	void OnMatchStateChanged(ESTU_MatchState State);
	void UpdatePlayerStat();
};
