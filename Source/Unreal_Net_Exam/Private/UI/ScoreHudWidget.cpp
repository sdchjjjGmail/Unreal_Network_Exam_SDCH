// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ScoreHudWidget.h"
#include "UI/ScoreDataWidget.h"

void UScoreHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Score->UpdateIntValue(0);
}

void UScoreHudWidget::UpdateScore(int32 NewScore)
{
	Score->UpdateIntValue(NewScore);
}
