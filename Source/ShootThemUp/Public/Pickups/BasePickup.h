// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ABasePickup();

	bool CouldBeTaken() const;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
		USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		float RespawnTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		float RotationYaw = 5.0f;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual bool GivePickupTo(APawn* PlayerPawn);

private:
	FTimerHandle RespawnTimerHandle;

	void PickupWasTaken();
	void Respawn();

};
