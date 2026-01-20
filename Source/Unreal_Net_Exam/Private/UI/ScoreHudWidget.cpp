// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/ScoreHudWidget.h"
#include "UI/ScoreDataWidget.h"
#include "Framework/ExamPlayerState.h"
#include "Framework/ExamGameState.h"
#include "Components/VerticalBox.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void UScoreHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bBuilt = false;

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

void UScoreHudWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!CachedGameState.IsValid())
	{
		CachedGameState = Cast<AExamGameState>(UGameplayStatics::GetGameState(this));
	}

	UpdateTimeDisplay();
	UpdateGameOverDisplay();
}

void UScoreHudWidget::UpdateTimeDisplay()
{
	if (CachedGameState.IsValid())
	{
		int32 Total = FMath::FloorToInt(CachedGameState->GetGameElapsedTime());
		int32 Minutes = Total / 60;
		int32 Seconds = Total % 60;

		Total = FMath::FloorToInt(CachedGameState->GetGameRemainingTime());
		Minutes = Total / 60;
		Seconds = Total % 60;
		RemainingTimeText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds)));
	}
}

void UScoreHudWidget::UpdateGameOverDisplay()
{
	if (bResultShown) return;
	if (!CachedGameState.IsValid()) return;

	if (!CachedGameState->IsGameOver())
	{
		return;
	}

	APlayerController* PC = GetOwningPlayer();
	if (!PC) return;

	APlayerState* MyPS = PC->PlayerState;
	if (!MyPS) return;

	const bool bWin = CachedGameState->IsWinner(MyPS);

	if (ResultText)
	{
		ResultText->SetVisibility(ESlateVisibility::Visible);
		ResultText->SetText(bWin ? FText::FromString(TEXT("Win!")) : FText::FromString(TEXT("Lose")));
	}

	bResultShown = true;
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
