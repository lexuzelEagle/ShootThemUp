// Shoot Them Up Game. All Rights Reserved


#include "UI/STUHUD.h"
#include "Engine/Canvas.h"
#include "UI/STU_BaseWidget.h"
#include "STUGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUHUD, All, All);

void ASTUHUD::BeginPlay()
{
	Super::BeginPlay();

	GameWidgets.Add(ESTU_MatchState::InProgress, CreateWidget<USTU_BaseWidget>(GetWorld(), PlayerHudWidgetClass));
	GameWidgets.Add(ESTU_MatchState::Pause, CreateWidget<USTU_BaseWidget>(GetWorld(), PauseWidgetClass));
	GameWidgets.Add(ESTU_MatchState::GameOver, CreateWidget<USTU_BaseWidget>(GetWorld(), GameOverWidgetClass));

	for (auto GameWidgetPair : GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if (!GameWidget) continue;

		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}

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
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
	}

	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
		CurrentWidget->Show();
	}

	UE_LOG(LogSTUHUD, Display, TEXT("Match State changed: %s"), *UEnum::GetValueAsString(State));
}
