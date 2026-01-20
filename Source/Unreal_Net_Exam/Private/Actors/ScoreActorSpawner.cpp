// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ScoreActorSpawner.h"
#include "Components/BoxComponent.h"

AScoreActorSpawner::AScoreActorSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = false;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SetRootComponent(SpawnArea);

	SpawnArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnArea->SetBoxExtent(FVector(1300, 1600, 150));
}

void AScoreActorSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority())
	{
		return;
	}

	const bool bSpawnImmediately = true;
	if (bSpawnImmediately)
	{
		Server_SpawnOnce();
	}

	GetWorldTimerManager().SetTimer(
		SpawnHandle,
		this,
		&AScoreActorSpawner::Server_SpawnOnce,
		SpawnInterval,
		true
	);
}

void AScoreActorSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (HasAuthority())
	{
		GetWorldTimerManager().ClearTimer(SpawnHandle);
	}
	Super::EndPlay(EndPlayReason);
}

bool AScoreActorSpawner::GetRandomPointInBox(FVector& OutLocation) const
{
	if (!SpawnArea) return false;

	const FVector Origin = SpawnArea->GetComponentLocation();
	const FVector Extent = SpawnArea->GetScaledBoxExtent();

	const FVector TraceStart(
		Origin.X + FMath::FRandRange(-Extent.X, Extent.X),
		Origin.Y + FMath::FRandRange(-Extent.Y, Extent.Y),
		Origin.Z + Extent.Z + 200.f
	);

	const FVector TraceEnd = TraceStart - FVector(0, 0, 50000.f);

	FHitResult Hit;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(ScoreSpawnTrace), false);
	Params.bTraceComplex = false;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_WorldStatic, Params))
	{
		OutLocation = Hit.ImpactPoint + FVector(0, 0, SpawnZOffset);
		return true;
	}

	return false;
}

void AScoreActorSpawner::Server_SpawnOnce()
{
	if (!HasAuthority()) return;
	if (!SpawnClass) return;

	FVector SpawnLoc;
	if (!GetRandomPointInBox(SpawnLoc)) return;
	

	const FRotator SpawnRot = FRotator::ZeroRotator;

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AActor* Spawned = GetWorld()->SpawnActor<AActor>(SpawnClass, SpawnLoc, SpawnRot, Params);
}