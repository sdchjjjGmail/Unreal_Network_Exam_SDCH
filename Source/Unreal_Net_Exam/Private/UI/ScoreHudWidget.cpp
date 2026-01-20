// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/ScoreHudWidget.h"
#include "UI/ScoreDataWidget.h"
#include "Framework/ExamPlayerState.h"

#include "Components/VerticalBox.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "TimerManager.h"

void UScoreHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bBuilt = false;
	LastSignature = 0;

	TryBuildScoreboard();
}

void UScoreHudWidget::NativeDestruct()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(BuildRetryHandle);
		World->GetTimerManager().ClearTimer(WatchHandle);
	}

	Super::NativeDestruct();
}

void UScoreHudWidget::TryBuildScoreboard()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	AGameStateBase* GS = World->GetGameState();
	if (!GS || GS->PlayerArray.Num() == 0 || !ScoreList || !ScoreRowClass)
	{
		World->GetTimerManager().SetTimer(
			BuildRetryHandle,
			this,
			&UScoreHudWidget::TryBuildScoreboard,
			0.2f,
			false
		);
		return;
	}

	BuildScoreboard(GS);
	bBuilt = true;

	World->GetTimerManager().SetTimer(
		WatchHandle,
		[this]()
		{
			UWorld* World = GetWorld();
			if (!World) return;

			AGameStateBase* GS = World->GetGameState();
			if (!GS) return;

			BuildScoreboard(GS);
		},
		0.5f,
		true
	);
}

void UScoreHudWidget::BuildScoreboard(AGameStateBase* InGS)
{
	if (!ScoreList || !ScoreRowClass || !InGS)
	{
		return;
	}

	ScoreList->ClearChildren();

	for (APlayerState* BasePS : InGS->PlayerArray)
	{
		AExamPlayerState* PS = Cast<AExamPlayerState>(BasePS);
		if (!PS)
		{
			continue;
		}

		UScoreDataWidget* Row = CreateWidget<UScoreDataWidget>(GetOwningPlayer(), ScoreRowClass);
		if (!Row)
		{
			continue;
		}

		Row->Init(PS);

		ScoreList->AddChild(Row);
	}
}
