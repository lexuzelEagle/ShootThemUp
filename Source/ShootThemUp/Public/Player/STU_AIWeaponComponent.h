// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Player/WeaponComponent.h"
#include "STU_AIWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTU_AIWeaponComponent : public UWeaponComponent
{
	GENERATED_BODY()
	
public:
	virtual void FireStart() override;
	virtual void NextWeapon() override;
};
