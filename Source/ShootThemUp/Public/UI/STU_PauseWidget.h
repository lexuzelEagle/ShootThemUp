// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STU_PauseWidget.generated.h"

class UButton;

UCLASS()
class SHOOTTHEMUP_API USTU_PauseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta = (BindWidget))
		UButton* ClearPauseButton;

private:
	UFUNCTION()
		void OnClearPause();
};
