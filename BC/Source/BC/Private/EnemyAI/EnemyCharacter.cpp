// Fill out your copyright notice in the Description page of Project Settings.

#include "BC.h"
#include "EnemyAI/EnemyCharacter.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Health = MaxHealth;
	Super::BeginPlay();
}

// Called every frame
void AEnemyCharacter::Tick( float DeltaTime )
{
	APawn *player = UGameplayStatics::GetPlayerPawn(this, 0);

	UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
	float const Distance = FVector::Dist(player->GetActorLocation(), GetActorLocation());

	// We need to issue move command only if far enough in order for walk animation to play correctly
	if (NavSys && (Distance > MinimumDistance))
	{
		NavSys->SimpleMoveToLocation(GetController(), player->GetActorLocation());
	}

	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

//take damage function
float AEnemyCharacter::TakeDamage(float damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(damage, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage > 0.0f)
	{
		Health -= ActualDamage;
		if (Health <= 0.0f)
		{
			HandleDeath();
		}
	}
	return ActualDamage;
}

void AEnemyCharacter::HandleDeath()
{
	//Handle Death of enemy unit
	SetActorLocation(FVector(0, 0, 0));
	Health = MaxHealth;
}
