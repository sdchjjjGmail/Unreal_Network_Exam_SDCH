// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreHudWidget.generated.h"

class UScoreDataWidget;

/**
 * 
 */
UCLASS()
class UNREAL_NET_EXAM_API UScoreHudWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateScore(int32 NewScore);

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UScoreDataWidget> Score;

private:
	TWeakObjectPtr<class APlayerStateCharacter> OwningPlayerCharacter = nullptr;
};
