#pragma once

#include "BCWeapon.h"
#include "GameFramework/Actor.h"
#include "BCAssaultRifle.generated.h"

UCLASS()
class BC_API ABCAssaultRifle : public ABCWeapon
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABCAssaultRifle(const FObjectInitializer&);

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;

    virtual void OnBeginFire() override;
    virtual void OnEndFire() override;

protected:
    UPROPERTY(EditAnywhere, Category = WeaponStats)
    float FireRate = 0.1f;

    UPROPERTY(EditAnywhere, Category = WeaponStats)
    float WeaponRange = 10000.0f;

    UPROPERTY(EditAnywhere, Category = WeaponStats)
    float ShotDamage = 10.0f;

private:
    FTimerHandle WeaponTimer;

    void TraceShot();
};
