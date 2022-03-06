// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "Dev/STUCoreUtils.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerHudWidget.generated.h"

class UWeaponComponent;
class USTUHealthComponent;

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
};
