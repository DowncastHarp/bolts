// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "BC.h"
#include "BCCharacter.h"
#include "Player/Weapons/BCAssaultRifle.h"

#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"

ABCCharacter::ABCCharacter()
{
    // Set size for player capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Don't rotate character to camera direction
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
    GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->bSnapToPlaneAtStart = true;

    // Create a camera boom...
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
    CameraBoom->TargetArmLength = 800.f;
    CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
    CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

    // Create a camera...
    TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
    TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

    // Create a decal in the world to show the cursor's location
    CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
    CursorToWorld->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
    if (DecalMaterialAsset.Succeeded()) {
        CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
    }
    CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
    CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

    // Activate ticking in order to update the cursor every frame.
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
}

void ABCCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (WeaponClass) {
        UWorld* World = GetWorld();
        if (World) {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = Instigator;

            Weapon = World->SpawnActor<ABCAssaultRifle>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

            if (Weapon) {
                Weapon->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
                Weapon->SetPlayer(this);
            }
        }
    }
}

void ABCCharacter::Tick(float DeltaSeconds)
{
    if (CursorToWorld != nullptr) {
        if (APlayerController* PC = Cast<APlayerController>(GetController())) {
            FHitResult TraceHitResult;
            PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
            FVector CursorFV = TraceHitResult.ImpactNormal;
            FRotator CursorR = CursorFV.Rotation();
            CursorToWorld->SetWorldLocation(TraceHitResult.Location);
            CursorToWorld->SetWorldRotation(CursorR);
        }
    }
}

float ABCCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = ACharacter::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

    if (ActualDamage > 0.0f) {
        Health -= ActualDamage;
        if (Health <= 0.0f) {
            // We're dead now, so we can't take damage
            bCanBeDamaged = false;

            HandleDeath();
        }
    }

    return ActualDamage;
}

void ABCCharacter::HandleDeath()
{
    // This should end the round and play a death animation among other things.
    // However, there's nothing to actually do right now, so keep do nothing.
}

void ABCCharacter::OnStartFire()
{
    if (Weapon) {
        Weapon->OnStartFire();
    }
}

void ABCCharacter::OnStopFire()
{
    if (Weapon) {
        Weapon->OnStopFire();
    }
}
