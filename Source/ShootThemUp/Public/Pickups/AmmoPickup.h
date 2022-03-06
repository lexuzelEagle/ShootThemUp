// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "AmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API AAmmoPickup : public ABasePickup
{
	GENERATED_BODY()

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
