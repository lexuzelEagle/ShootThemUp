#pragma once

#include "STUCoreUtils.generated.h"

class ASTUBaseWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<ASTUBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
		UAnimMontage* ReloadAnimMontage;
};

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
		int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		bool Infinite;
};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		UTexture2D* MainIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		UTexture2D* CrossHairIcon;

};

// VFX

USTRUCT(BlueprintType)
struct FDecalData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		UMaterialInterface* Material;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		FVector Size = FVector(10.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		float LifeTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		float FadeOutTime = 0.7f;

};


class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FImpactData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		UNiagaraSystem* NiagaraEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		FDecalData DecalData;
};


USTRUCT(BlueprintType)
struct FGameData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "100"))
		int32 PlayersNum = 2;
};


class Utils
{
public:

	template<typename T>
	static T* FindNotifyByClass(UAnimSequenceBase* Animation)
	{
		check(Animation);

		const auto NotifyEvents = Animation->Notifies;
		for (auto NotifyEvent : NotifyEvents)
		{
			auto AnimNotify = Cast<T>(NotifyEvent.Notify);
			if (AnimNotify)
			{
				return AnimNotify;
			}
		}

		return nullptr;
	}

	template<typename T>
	static T* GetComponent(AActor* Player)
	{
		if (!Player) return nullptr;

		const auto Component = Player->GetComponentByClass(T::StaticClass());
		return Cast<T>(Component);
	}
};