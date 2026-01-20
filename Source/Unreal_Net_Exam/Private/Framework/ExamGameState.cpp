// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/ExamGameState.h"
#include "Framework/ExamPlayerState.h"
#include "Net/UnrealNetwork.h"

AExamGameState::AExamGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AExamGameState::BeginPlay()
{
	Super::BeginPlay();
	GameRemainingTime = GameDuration;
}

void AExamGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority() && !bGameOver)
	{
		GameRemainingTime -= DeltaTime;

		if (GameRemainingTime <= 0.0f)
		{
			GameRemainingTime = 0.0f;
			bGameOver = true;

			DecideWinners_Server();
		}
	}
}

void AExamGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME(AExamGameState, GameRemainingTime);
	DOREPLIFETIME(AExamGameState, bGameOver);
	DOREPLIFETIME(AExamGameState, WinnerPlayerIds);
}

void AExamGameState::DecideWinners_Server()
{
	WinnerPlayerIds.Reset();

	int32 Best = TNumericLimits<int32>::Min();

	for (APlayerState* BasePS : PlayerArray)
	{
		AExamPlayerState* PS = Cast<AExamPlayerState>(BasePS);
		if (!PS) continue;

		const int32 Score = PS->GetMyScore();
		if (Score > Best)
		{
			Best = Score;
			WinnerPlayerIds.Reset();
			WinnerPlayerIds.Add(PS->GetPlayerId());
		}
		else if (Score == Best)
		{
			WinnerPlayerIds.Add(PS->GetPlayerId());
		}
	}
}

bool AExamGameState::IsWinner(const APlayerState* PS) const
{
	if (!PS) return false;
	return WinnerPlayerIds.Contains(PS->GetPlayerId());
}
