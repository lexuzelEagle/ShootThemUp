// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class USTUHealthComponent;
class UWeaponComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASTUBaseCharacter(const FObjectInitializer& ObjInit);

	UFUNCTION(BlueprintCallable)
	virtual bool IsRunning() const { return false; };

	void SetPlayerColor(const FLinearColor& Color);

protected:
	/* Properies Components */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USTUHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UWeaponComponent* WeaponComponent;

	/* Properies Movement */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		float MoveSpeedMultiplier = 2.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		bool IsAboutToRun = false;

	/* Animation */
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UAnimMontage* DeathAnimMontage;

	/* Damage */
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	UFUNCTION(BlueprintCallable, Category = "Damage")
		float GetMovementDirection() const;

	UPROPERTY(EditDefaultsOnly, Category = "Material")
		FName MaterialColorName = "Paint Color";

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnDeath();
	virtual void OnHealthChanged(float Health, float HealthDelta);

private:

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
};
