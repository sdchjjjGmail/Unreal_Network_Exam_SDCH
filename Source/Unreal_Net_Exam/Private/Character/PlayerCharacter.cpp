// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "Framework/ExamPlayerState.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::Server_AddScore_Implementation(int32 Point)
{
	AExamPlayerState* PS = GetPlayerState<AExamPlayerState>();
	if (PS)
	{
		PS->AddMyScore(Point);
	}
}

void APlayerCharacter::TestAddScore()
{
	if (IsLocallyControlled())
	{
		Server_AddScore(10);
	}
}
