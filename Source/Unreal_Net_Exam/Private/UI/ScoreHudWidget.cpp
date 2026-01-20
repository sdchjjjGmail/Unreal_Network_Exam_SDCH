// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ScoreHudWidget.h"

void UScoreHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Score->UpdateName(FText::FromString(TEXT("점수")));
	Score->UpdateIntValue(0);
}

void UScoreHudWidget::UpdateScore(int32 NewScore)
{
	Score->UpdateIntValue(NewScore);
}
