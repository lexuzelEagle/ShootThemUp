// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Dev/STUCoreUtils.h"
#include "STUHUD.generated.h"


UCLASS()
class SHOOTTHEMUP_API ASTUHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> PlayerHudWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> GameOverWidgetClass;

private:
	UPROPERTY()
		TMap<ESTU_MatchState, UUserWidget*> GameWidgets;

	UPROPERTY()
		UUserWidget* CurrentWidget = nullptr;

	void DrawCrossHair();
	void OnMatchStateChanged(ESTU_MatchState State);
};
