// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STU_MenuHUD.generated.h"


UCLASS()
class SHOOTTHEMUP_API ASTU_MenuHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> MenuWidgetClass;

	virtual void BeginPlay() override;
};
