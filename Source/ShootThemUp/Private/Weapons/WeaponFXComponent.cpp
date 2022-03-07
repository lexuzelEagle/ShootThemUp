// Shoot Them Up Game. All Rights Reserved


#include "Weapons/WeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"


UWeaponFXComponent::UWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto Effect = DefaultEffect;

	if (Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();
		if (EffectsMap.Contains(PhysMat))
		{
			Effect = EffectsMap[PhysMat];
		}
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}
