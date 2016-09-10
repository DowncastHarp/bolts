// Fill out your copyright notice in the Description page of Project Settings.

#include "BC.h"
#include "EnemyCharacterSpawn.h"


// Sets default values
AEnemyCharacterSpawn::AEnemyCharacterSpawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

