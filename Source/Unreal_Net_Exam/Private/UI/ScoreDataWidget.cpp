// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ScoreDataWidget.h"
#include "Components/TextBlock.h"
#include "Framework/ExamPlayerState.h"

void UScoreDataWidget::Init(AExamPlayerState* InPS)
{
	PS = InPS;
	if (!PS.IsValid()) return;

	OnScoreChanged(PS->GetMyScore());

	ScoreChangedHandle = PS->OnScoreChanged.AddUObject(
		this, &UScoreDataWidget::OnScoreChanged
	);
}

void UScoreDataWidget::OnScoreChanged(int32 NewScore)
{
	if (Value)
	{
		Value->SetText(FText::AsNumber(NewScore));
	}
}

void UScoreDataWidget::NativeDestruct()
{
	if (PS.IsValid() && ScoreChangedHandle.IsValid())
	{
		PS->OnScoreChanged.Remove(ScoreChangedHandle);
	}

	Super::NativeDestruct();
}