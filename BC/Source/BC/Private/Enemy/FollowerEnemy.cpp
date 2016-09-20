// Fill out your copyright notice in the Description page of Project Settings.

#include "BC.h"
#include "FollowerEnemy.h"


// Sets default values
AFollowerEnemy::AFollowerEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFollowerEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFollowerEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AFollowerEnemy::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

