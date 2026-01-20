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
	UFUNCTION(BlueprintCallable)
	void UpdateIntValue(int32 InValue);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Value = nullptr;
};
