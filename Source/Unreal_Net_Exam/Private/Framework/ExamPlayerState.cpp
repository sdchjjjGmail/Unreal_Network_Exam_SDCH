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
		OnRep_MyScore();
	}
}

void AExamPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AExamPlayerState, MyScore);
}

void AExamPlayerState::OnRep_MyScore()
{
	// UI 갱신
	UE_LOG(LogTemp, Log, TEXT("[%d]Score : %d"), GetPlayerId(), MyScore);
	if (!ScoreHud.IsValid())
	{
		if (GetPlayerController())
		{
			//UE_LOG(LogTemp, Log, TEXT("플레이어 컨트롤러 있음"));
			AMainHUD* HUD = GetPlayerController()->GetHUD<AMainHUD>();
			if (HUD && HUD->GetMainHudWidget().IsValid())
			{
				//UE_LOG(LogTemp, Log, TEXT("HUD와 HUD위젯도 있음"));
				ScoreHud = Cast<UScoreHudWidget>(HUD->GetMainHudWidget().Get());
			}
		}
	}
	if (ScoreHud.IsValid())
	{
		ScoreHud->UpdateScore(MyScore);
	}
}
