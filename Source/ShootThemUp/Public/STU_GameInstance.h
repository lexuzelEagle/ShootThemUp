// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STU_GameInstance.generated.h"


UCLASS()
class SHOOTTHEMUP_API USTU_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	FName GetStartupLevelName() const { return StartupLevelName; }
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
		FName StartupLevelName = NAME_None;
};
