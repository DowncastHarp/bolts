// Fill out your copyright notice in the Description page of Project Settings.

#include "BC.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnemySpawnVolume.h"
#include "EnemyCharacterSpawn.h"


// Sets default values
AEnemySpawnVolume::AEnemySpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawnVolumeBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolumeBox"));
	RootComponent = SpawnVolumeBox;

	SpawnDelayLimitLow = 1.0f;
	SpawnDelayLimitHigh = 4.5f;
	
}

// Called when the game starts or when spawned
void AEnemySpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	SpawnDelay = FMath::FRandRange(SpawnDelayLimitLow, SpawnDelayLimitHigh);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AEnemySpawnVolume::SpawnEnemyBoltOne, SpawnDelay, false);
	
}

// Called every frame
void AEnemySpawnVolume::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

FVector AEnemySpawnVolume::GetRandomSpawnLocations()
{
	FVector SpawnBoxOrigin = SpawnVolumeBox->Bounds.Origin;
	FVector SpawnBoxExtent = SpawnVolumeBox->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnBoxOrigin, SpawnBoxExtent);
}

void AEnemySpawnVolume::SpawnEnemyBoltOne()
{
	if (WhatToSpawn != NULL)
	{
		UWorld* const World = GetWorld();

		if (World)
		{
			FActorSpawnParameters SpawnParameters;

			SpawnParameters.Owner = this;
			SpawnParameters.Instigator = Instigator;

			FVector Location = GetRandomSpawnLocations();

			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.0f;
			SpawnRotation.Pitch = FMath::FRand() * 360.0f;
			SpawnRotation.Roll = FMath::FRand() * 360.0f;

			AEnemyCharacterSpawn* const SpawnedEnemy = World->SpawnActor<AEnemyCharacterSpawn>(WhatToSpawn, Location, SpawnRotation, SpawnParameters);

			SpawnDelay = FMath::FRandRange(SpawnDelayLimitLow, SpawnDelayLimitHigh);
			GetWorldTimerManager().SetTimer(SpawnTimer, this, &AEnemySpawnVolume::SpawnEnemyBoltOne, SpawnDelay, false);
		}
	}
}