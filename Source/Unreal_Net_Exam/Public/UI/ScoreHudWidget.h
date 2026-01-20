// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreHudWidget.generated.h"

class UVerticalBox;
class UScoreDataWidget;
class AGameStateBase;
class AExamPlayerState;

UCLASS()
class UNREAL_NET_EXAM_API UScoreHudWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void UpdateTimeDisplay();

	void UpdateGameOverDisplay();

private:
	UFUNCTION()
	void TryBuildScoreboard();

	void BuildScoreboard(AGameStateBase* GS);

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UTextBlock> RemainingTimeText = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ResultText = nullptr;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> ScoreList = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UScoreDataWidget> ScoreRowClass;

	TWeakObjectPtr<class AExamGameState> CachedGameState = nullptr;

	FTimerHandle BuildRetryHandle;

	FTimerHandle WatchHandle;

	bool bBuilt = false;
	bool bResultShown = false;
};
