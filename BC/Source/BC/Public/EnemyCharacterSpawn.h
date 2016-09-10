// Fill out your copyright notice in the Description page of Project Settings.
//Parent Class for setting common enemy characteristics
#pragma once

#include "GameFramework/Character.h"
#include "EnemyCharacterSpawn.generated.h"

UCLASS()
class BC_API AEnemyCharacterSpawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacterSpawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/** Returns the enemy mesh */
	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return EnemyMesh; }
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* EnemyMesh;
};
