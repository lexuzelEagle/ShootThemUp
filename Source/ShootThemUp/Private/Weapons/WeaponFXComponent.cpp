// Shoot Them Up Game. All Rights Reserved


#include "Weapons/WeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"


UWeaponFXComponent::UWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}
