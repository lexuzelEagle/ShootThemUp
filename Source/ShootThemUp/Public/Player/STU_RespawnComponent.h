// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STU_RespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTU_RespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTU_RespawnComponent();

	void Respawn(int32 RespawnTime);
	int32 GetRespawnCountDown() const { return RespawnCountDown; }
	bool IsRespawnInProgress() const;
private:
	FTimerHandle RespawnTimerHandle;
	int32 RespawnCountDown = 0;
	
	void UpdateTimer();
};
