// Fill out your copyright notice in the Description page of Project Settings.

#include "BC.h"
#include "EnemyCharacterSpawn.h"


// Sets default values
AEnemyCharacterSpawn::AEnemyCharacterSpawn()
{
 	// Character Tick() turned off to improve performance.
	PrimaryActorTick.bCanEverTick = false;

	/** Create the enemy static mesh component and set it to be the root component */
	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	RootComponent = EnemyMesh;

}

// Called when the game starts or when spawned
void AEnemyCharacterSpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacterSpawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AEnemyCharacterSpawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

