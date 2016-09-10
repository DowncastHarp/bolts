// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnemySpawnVolume.generated.h"

UCLASS()
class BC_API AEnemySpawnVolume : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AEnemySpawnVolume();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;

    FORCEINLINE class UBoxComponent* GetSpawnVolumeBox() const
    {
        return SpawnVolumeBox;
    }

    UFUNCTION(BlueprintPure, Category = "Spawn Volume Parameters")
    FVector GetRandomSpawnLocations();

protected:
    UPROPERTY(EditAnywhere, Category = "Spawn Volume Parameters")
    TSubclassOf<class AEnemyCharacterSpawn> WhatToSpawn;

    FTimerHandle SpawnTimer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Spawn Volume Parameters")
    float SpawnDelayLimitLow;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Spawn Volume Parameters")
    float SpawnDelayLimitHigh;
private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn Volume Parameters", meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* SpawnVolumeBox;

    // Function to spawn the enemy of type EnemyBoltOne
    void SpawnEnemyBoltOne();

    float SpawnDelay;
};
