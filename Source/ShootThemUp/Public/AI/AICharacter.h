// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "AICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class SHOOTTHEMUP_API AAICharacter : public ASTUBaseCharacter
{
	GENERATED_BODY()

public:
	AAICharacter(const FObjectInitializer& ObjInit);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		UBehaviorTree* BehaviorTreeAsset;

protected:
	virtual void OnDeath() override;
};
