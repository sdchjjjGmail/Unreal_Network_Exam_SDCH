// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/ExamPlayerState.h"
#include "Framework/MainHUD.h"
#include "Net/UnrealNetwork.h"
#include "UI/ScoreHudWidget.h"

void AExamPlayerState::AddMyScore(int32 Point)
{
	if (HasAuthority())
	{
		MyScore += Point;
		OnScoreChanged.Broadcast(MyScore);
	}
}

void AExamPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AExamPlayerState, MyScore);
}

void AExamPlayerState::OnRep_MyScore()
{	
	OnScoreChanged.Broadcast(MyScore);
}
