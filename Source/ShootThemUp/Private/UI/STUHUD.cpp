// Shoot Them Up Game. All Rights Reserved


#include "UI/STUHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "STUGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUHUD, All, All);

void ASTUHUD::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerHudWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHudWidgetClass);
	check(PlayerHudWidget);

	PlayerHudWidget->AddToViewport();

	if (GetWorld())
	{
		const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &ASTUHUD::OnMatchStateChanged);
		}
	}
}

void ASTUHUD::DrawHUD()
{
	Super::DrawHUD();
}

void ASTUHUD::DrawCrossHair()
{
	FVector2D Center(Canvas->SizeX / 2, Canvas->SizeY / 2);
	float LineHalfLength = 10.0f;
	float LineThickness = 2.0f;
	FLinearColor LineColor = FLinearColor::Green;

	DrawLine(Center.X - LineHalfLength, Center.Y, Center.X + LineHalfLength, Center.Y, LineColor, LineThickness);
	DrawLine(Center.X, Center.Y - LineHalfLength, Center.X, Center.Y + LineHalfLength, LineColor, LineThickness);
}

void ASTUHUD::OnMatchStateChanged(ESTU_MatchState State)
{
	UE_LOG(LogSTUHUD, Display, TEXT("Match State changed: %s"), *UEnum::GetValueAsString(State));
}
