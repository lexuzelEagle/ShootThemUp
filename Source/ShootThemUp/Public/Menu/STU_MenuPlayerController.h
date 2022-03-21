// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STU_MenuPlayerController.generated.h"


UCLASS()
class SHOOTTHEMUP_API ASTU_MenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};
