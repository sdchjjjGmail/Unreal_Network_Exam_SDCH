// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ScoreActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Framework/ExamPlayerState.h"

AScoreActor::AScoreActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->InitSphereRadius(25.0f);
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
}

void AScoreActor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		Collision->OnComponentBeginOverlap.AddDynamic(this, &AScoreActor::GiveScore);
	}
}

void AScoreActor::GiveScore(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		ACharacter* Character = Cast<ACharacter>(OtherActor);
		if (Character)
		{
			AExamPlayerState* PS = Character->GetPlayerState<AExamPlayerState>();
			if (PS)
			{
				PS->AddMyScore(Point);
				Destroy();
			}
		}
	}
}
