// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "Dev/STUCoreUtils.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerHudWidget.generated.h"

class UWeaponComponent;
class USTUHealthComponent;
class ASTUGameModeBase;
class ASTU_PlayerState;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerHudWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerSpectating() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTakeDamage();

	virtual bool Initialize() override;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetKillsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetDeathsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetCurrentRoundNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetTotalRoundsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetRoundSecondsRemaining() const;

private:
	void OnHealthChanged(float Health, float HealthDelta);

	ASTUGameModeBase* GetGameMode() const;
	ASTU_PlayerState* GetPlayerState() const;

};
