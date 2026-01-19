// Copyright Epic Games, Inc. All Rights Reserved.

#include "Unreal_Net_ExamGameMode.h"
#include "Unreal_Net_ExamCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnreal_Net_ExamGameMode::AUnreal_Net_ExamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
