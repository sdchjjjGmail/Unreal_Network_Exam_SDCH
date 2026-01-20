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

private:
	UFUNCTION()
	void TryBuildScoreboard();

	void BuildScoreboard(AGameStateBase* GS);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> ScoreList = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UScoreDataWidget> ScoreRowClass;

private:
	FTimerHandle BuildRetryHandle;

	FTimerHandle WatchHandle;

	bool bBuilt = false;

	uint32 LastSignature = 0;
};
