// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponFXComponent.generated.h"

class UPhysicalMaterial;
class UNiagaraSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API UWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponFXComponent();

	void PlayImpactFX(const FHitResult& Hit);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		UNiagaraSystem* DefaultEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		TMap<UPhysicalMaterial*, UNiagaraSystem*> EffectsMap;

};
