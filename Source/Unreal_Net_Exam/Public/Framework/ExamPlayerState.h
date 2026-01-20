// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ExamPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int32);

/**
 * 
 */
UCLASS()
class UNREAL_NET_EXAM_API AExamPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddMyScore(int32 Point);

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetMyScore() const { return MyScore; }

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_MyScore();

public:
	FOnScoreChanged OnScoreChanged;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_MyScore, BlueprintReadOnly, Category = "Data")
	int32 MyScore = 0;

	TWeakObjectPtr<class UScoreHudWidget> ScoreHud = nullptr;
};
