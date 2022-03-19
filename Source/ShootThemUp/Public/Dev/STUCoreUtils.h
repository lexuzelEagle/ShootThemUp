#pragma once

#include "Player/STU_PlayerState.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
		int32 RoundsNum = 4;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "300"))
		int32 RoundTime = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FLinearColor DefaultTeamColor = FLinearColor::Red;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray<FLinearColor> TeamColors;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "30"))
		int32 RespawnTime = 5;
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

	static bool AreEnemies(AController* Controller1, AController* Controller2)
	{
		if (!Controller1 || !Controller2 || Controller1 == Controller2) return false;

		const auto PlayerState1 = Cast<ASTU_PlayerState>(Controller1->PlayerState);
		const auto PlayerState2 = Cast<ASTU_PlayerState>(Controller2->PlayerState);

		return PlayerState1 && PlayerState2 && PlayerState1->GetTeamID() != PlayerState2->GetTeamID();
	}

	static FText TextFromInt(int32 Number) 
	{
		return FText::FromString(FString::FromInt(Number));
	}
};

UENUM(BlueprintType)
enum class ESTU_MatchState : uint8
{
	WaitingToStart = 0,
	InProgress,
	Pause,
	GameOver
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, ESTU_MatchState);