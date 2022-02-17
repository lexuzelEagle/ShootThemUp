// Shoot Them Up Game. All Rights Reserved


#include "UI/STUHUD.h"
#include "Engine/Canvas.h"

void ASTUHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawCrossHair();
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
