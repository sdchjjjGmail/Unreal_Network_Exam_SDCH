// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreActorSpawner.generated.h"

UCLASS()
class UNREAL_NET_EXAM_API AScoreActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:
	AScoreActorSpawner();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void Server_SpawnOnce();

	bool GetRandomPointInBox(FVector& OutLocation) const;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Spawner")
	TObjectPtr<class UBoxComponent> SpawnArea = nullptr;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TSubclassOf<AActor> SpawnClass;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnInterval = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnZOffset = 20.0f;

private:
	FTimerHandle SpawnHandle;
};
