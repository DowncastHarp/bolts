#pragma once

#include "GameFramework/Actor.h"
#include "BCAssaultRifle.generated.h"

class ABCCharacter;

UCLASS()
class BC_API ABCAssaultRifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABCAssaultRifle(const FObjectInitializer&);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

  void OnStartFire();
  void OnStopFire();

  void TraceShot();

  ABCCharacter* GetPlayer() {
    return Player;
  }
  void SetPlayer(ABCCharacter* Player) {
    this->Player = Player;
  }
protected:
  UPROPERTY(EditAnywhere, Category = WeaponStats)
  float FireRate = 0.1f;

  UPROPERTY(EditAnywhere, Category = WeaponStats)
  float WeaponRange = 10000.0f;

  UPROPERTY(EditAnywhere, Category = WeaponStats)
  float ShotDamage = 10.0f;

private:
  ABCCharacter* Player;
  FTimerHandle WeaponTimer;
};
