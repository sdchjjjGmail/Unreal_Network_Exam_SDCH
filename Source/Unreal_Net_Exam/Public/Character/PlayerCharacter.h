// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class UNREAL_NET_EXAM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable)
	void Server_AddScore(int32 Point);

public:
	UFUNCTION(BlueprintCallable, Category = "Test")
	void TestAddScore();
};
