// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "BCCharacter.generated.h"

class ABCWeapon;

UCLASS(Blueprintable)
class ABCCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ABCCharacter();

    void BeginPlay() override;

    // Called every frame.
    virtual void Tick(float DeltaSeconds) override;

    /** Returns TopDownCameraComponent subobject **/
    FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const
    {
        return TopDownCameraComponent;
    }
    /** Returns CameraBoom subobject **/
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const
    {
        return CameraBoom;
    }

    float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
    void HandleDeath();

    void OnBeginFirePrimary();
    void OnEndFirePrimary();

protected:
    UPROPERTY(EditAnywhere, Category = "Stats")
    float Health = 100.0f;

    UPROPERTY(EditAnywhere, Category = Weapon)
    TSubclassOf<class ABCWeapon> WeaponClass;

private:
    /** Top down camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* TopDownCameraComponent;

    /** Camera boom positioning the camera above the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom;

    /** A decal that projects to the cursor location. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UDecalComponent* CursorToWorld;

    /** The player's equipped weapon. */
    ABCWeapon* Weapon;
};

