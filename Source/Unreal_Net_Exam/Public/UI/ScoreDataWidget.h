// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreDataWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class UNREAL_NET_EXAM_API UScoreDataWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init(class AExamPlayerState* InPS);

	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnScoreChanged(int32 NewScore);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Value = nullptr;

private:
	TWeakObjectPtr<AExamPlayerState> PS;
	FDelegateHandle ScoreChangedHandle;
};
