// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class BC_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Damage)
	float Health;

	UPROPERTY(EditAnywhere, Category = Damage)
	float Damage;

	UPROPERTY(EditAnywhere, Category = Damage)
	float MaxHealth;
	
	UPROPERTY(EditAnywhere, Category = Damage)
	float MinimumDistance;

public:

	// Sets default values for this character's properties
	AEnemyCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Handle Death
	void HandleDeath();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	
};
