// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "BC.h"
#include "BCPlayerController.h"
#include "BCCharacter.h"
#include "AI/Navigation/NavigationSystem.h"

ABCPlayerController::ABCPlayerController()
{
    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ABCPlayerController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);

    // keep updating the destination every tick while desired
    if (bMoveToMouseCursor) {
        MoveToMouseCursor();
    }
}

void ABCPlayerController::SetupInputComponent()
{
    // set up gameplay key bindings
    Super::SetupInputComponent();

    InputComponent->BindAction("SetDestination", IE_Pressed, this, &ABCPlayerController::OnSetDestinationPressed);
    InputComponent->BindAction("SetDestination", IE_Released, this, &ABCPlayerController::OnSetDestinationReleased);

    // support touch devices
    InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ABCPlayerController::MoveToTouchLocation);
    InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ABCPlayerController::MoveToTouchLocation);

    InputComponent->BindAction("Fire", IE_Pressed, this, &ABCPlayerController::OnStartFire);
    InputComponent->BindAction("Fire", IE_Released, this, &ABCPlayerController::OnStopFire);
}

void ABCPlayerController::MoveToMouseCursor()
{
    // Trace to see what is under the mouse cursor
    FHitResult Hit;
    GetHitResultUnderCursor(ECC_Visibility, false, Hit);

    if (Hit.bBlockingHit) {
        // We hit something, move there
        SetNewMoveDestination(Hit.ImpactPoint);
    }
}

void ABCPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
    FVector2D ScreenSpaceLocation(Location);

    // Trace to see what is under the touch location
    FHitResult HitResult;
    GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
    if (HitResult.bBlockingHit) {
        // We hit something, move there
        SetNewMoveDestination(HitResult.ImpactPoint);
    }
}

void ABCPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
    APawn* const Pawn = GetPawn();
    if (Pawn) {
        UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
        float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

        // We need to issue move command only if far enough in order for walk animation to play correctly
        if (NavSys && (Distance > 120.0f)) {
            NavSys->SimpleMoveToLocation(this, DestLocation);
        }
    }
}

void ABCPlayerController::OnSetDestinationPressed()
{
    // set flag to keep updating destination until released
    bMoveToMouseCursor = true;
}

void ABCPlayerController::OnSetDestinationReleased()
{
    // clear flag to indicate we should stop updating the destination
    bMoveToMouseCursor = false;
}

void ABCPlayerController::OnStartFire()
{
    APawn* Pawn = GetPawn();
    if (Pawn) {
        Cast<ABCCharacter>(Pawn)->OnStartFire();
    }
}

void ABCPlayerController::OnStopFire()
{
    APawn* Pawn = GetPawn();
    if (Pawn) {
        Cast<ABCCharacter>(Pawn)->OnStopFire();
    }
}
