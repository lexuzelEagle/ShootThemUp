// Shoot Them Up Game. All Rights Reserved


#include "UI/STU_HealthBarWidget.h"
#include "Components/ProgressBar.h"


void USTU_HealthBarWidget::SetHealthPercent(float Percent)
{
	if (!HealthProgressBar) return;

	const auto HealthBarVisibility = (Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent))
									  ? ESlateVisibility::Hidden : ESlateVisibility::Visible;

	HealthProgressBar->SetVisibility(HealthBarVisibility);

	const auto HealthBarColor = Percent > PercentColorThreshold ? GoodColor : BadColor;
	HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

	HealthProgressBar->SetPercent(Percent);
}