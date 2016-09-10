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

	FORCEINLINE class UBoxComponent* GetSpawnVolumeBox() const { return SpawnVolumeBox; }

	UFUNCTION(BlueprintPure, Category = "Enemy")
	FVector GetRandomSpawnLocations();
	
protected:
	UPROPERTY(EditAnywhere, Category = "Enemy")
	TSubclassOf<class AEnemyCharacterSpawn> WhatToSpawn;

	FTimerHandle SpawnTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Enemy")
	float SpawnDelayLimitLow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Enemy")
	float SpawnDelayLimitHigh;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* SpawnVolumeBox;
	
	void SpawnEnemyBoltOne();

	float SpawnDelay; 
};
