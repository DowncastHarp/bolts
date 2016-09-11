#include "BC.h"
#include "Player/Weapons/BCAssaultRifle.h"

#include "BCCharacter.h"

#include "DrawDebugHelpers.h"

// Sets default values
ABCAssaultRifle::ABCAssaultRifle(const FObjectInitializer& ObjectInitalizer)
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    auto Scene = ObjectInitalizer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
    Scene->SetMobility(EComponentMobility::Movable);
    RootComponent = Scene;
}

// Called when the game starts or when spawned
void ABCAssaultRifle::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ABCAssaultRifle::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );

}

void ABCAssaultRifle::OnStartFire()
{
    GetWorldTimerManager().SetTimer(WeaponTimer, this, &ABCAssaultRifle::TraceShot, FireRate, true, -FireRate);
}

void ABCAssaultRifle::OnStopFire()
{
    GetWorldTimerManager().ClearTimer(WeaponTimer);
}

void ABCAssaultRifle::TraceShot()
{
    const FVector StartPos = Player->GetActorLocation();
    const FVector ForwardVec = Player->GetActorForwardVector();
    const FVector EndPos = StartPos + ForwardVec * WeaponRange;

    FCollisionQueryParams TraceParams(FName(TEXT("WeaponFireTag")), true, Instigator);
    TraceParams.bTraceAsyncScene = true;
    TraceParams.bReturnPhysicalMaterial = true;

    FHitResult Hit(ForceInit);
    GetWorld()->LineTraceSingleByObjectType(Hit, StartPos, EndPos, FCollisionObjectQueryParams::AllObjects, TraceParams);
    if (Hit.bBlockingHit) {
        // There's no actors to hit right now, so for now draw a debug line.
        DrawDebugLine(GetWorld(), StartPos, Hit.ImpactPoint, FColor::Cyan, false, 0.5f, 0, 1.5f);
    }
}
