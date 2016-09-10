// Fill out your copyright notice in the Description page of Project Settings.

#include "BC.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnemySpawnVolume.h"
#include "EnemyCharacterSpawn.h"
#define ROTATION_FACTOR 360.0f
#define SPAWN_DELAY_LOW 1.0f
#define SPAWN_DELAY_HIGH 4.5f

// Sets default values
AEnemySpawnVolume::AEnemySpawnVolume()
{
    // Character Tick() turned off to improve performance.
    PrimaryActorTick.bCanEverTick = false;

    SpawnVolumeBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolumeBox"));
    RootComponent = SpawnVolumeBox;

    SpawnDelayLimitLow = SPAWN_DELAY_LOW;
    SpawnDelayLimitHigh = SPAWN_DELAY_HIGH;

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

    // Return a random position in the spawn volume
    return UKismetMathLibrary::RandomPointInBoundingBox(SpawnBoxOrigin, SpawnBoxExtent);
}

void AEnemySpawnVolume::SpawnEnemyBoltOne()
{
    // Check if we have a valid mesh to spawn
    if (WhatToSpawn != NULL) {
        UWorld* const World = GetWorld();
        //Check if the world is still active/valid
        if (World) {
            FActorSpawnParameters SpawnParameters;

            SpawnParameters.Owner = this;
            SpawnParameters.Instigator = Instigator;

            FVector Location = GetRandomSpawnLocations();

            FRotator SpawnRotation;
            SpawnRotation.Yaw = FMath::FRand() * ROTATION_FACTOR;
            SpawnRotation.Pitch = FMath::FRand() * ROTATION_FACTOR;
            SpawnRotation.Roll = FMath::FRand() * ROTATION_FACTOR;

            AEnemyCharacterSpawn* const SpawnedEnemy = World->SpawnActor<AEnemyCharacterSpawn>(WhatToSpawn, Location, SpawnRotation, SpawnParameters);

            SpawnDelay = FMath::FRandRange(SpawnDelayLimitLow, SpawnDelayLimitHigh);
            GetWorldTimerManager().SetTimer(SpawnTimer, this, &AEnemySpawnVolume::SpawnEnemyBoltOne, SpawnDelay, false);
        }
    }
}