// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ScoreDataWidget.h"
#include "Components/TextBlock.h"

void UScoreDataWidget::UpdateIntValue(int32 InValue)
{
	Value->SetText(FText::AsNumber(InValue));
}
