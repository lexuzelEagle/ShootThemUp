// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Dev/STUCoreUtils.h"
#include "STU_GameInstance.generated.h"


UCLASS()
class SHOOTTHEMUP_API USTU_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	FLevelData GetStartupLevel() const { return StartupLevel; }
	void SetStartupLevel(const FLevelData& LevelData) { StartupLevel = LevelData; }

	TArray<FLevelData> GetLevelData() const { return LevelsData; }

	FName GetMenuLevelName() const { return MenuLevelName; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ToolTip = "Level names must be unique"))
		TArray<FLevelData> LevelsData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
		FName MenuLevelName = "MenuLevel";

private:
	FLevelData StartupLevel;
};
