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
    virtual void OnBeginFire() PURE_VIRTUAL(ABCWeapon::OnBeginFire, ;);

    // Called by the player when the weapon should stop firing.
    virtual void OnEndFire() PURE_VIRTUAL(ABCWeapon::OnEndFire, ;);

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
