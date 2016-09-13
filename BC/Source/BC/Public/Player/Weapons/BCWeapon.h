#pragma once

#include "GameFramework/Actor.h"
#include "BCWeapon.generated.h"

class ABCCharacter;

UCLASS(abstract)
class BC_API ABCWeapon : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABCWeapon();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;

    // Called by the player when the weapon should start firing.
    virtual void OnStartFire() PURE_VIRTUAL(ABCWeapon::OnStartFire, ;);

    // Called by the player when the weapon should stop firing.
    virtual void OnStopFire() PURE_VIRTUAL(ABCWeapon::OnStartFire, ;);

    // Returns the player who owns this weapon.
    ABCCharacter* GetPlayer()
    {
        return Player;
    }

    // Sets the player who owns this weapon.
    void SetPlayer(ABCCharacter* Player)
    {
        this->Player = Player;
    }

protected:
    ABCCharacter* Player;
};
