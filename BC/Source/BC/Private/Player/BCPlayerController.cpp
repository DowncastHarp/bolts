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

    // Update Rotation
    APawn* const Pawn = GetPawn();

    if (Pawn) {
        FVector rotInput(storedRotationX, storedRotationY, 0.0f);
        Pawn->SetActorRotation(rotInput.Rotation());
    }
}

void ABCPlayerController::SetupInputComponent()
{
    // set up gameplay key bindings
    Super::SetupInputComponent();

    // Gamepad Bindings

    // Movement Axis Bindings
    InputComponent->BindAxis("MoveForward", this, &ABCPlayerController::OnMoveForward);
    InputComponent->BindAxis("MoveRight", this, &ABCPlayerController::OnMoveRight);

    // Rotation Axis Bindings
    InputComponent->BindAxis("RotationX", this, &ABCPlayerController::OnRotateX);
    InputComponent->BindAxis("RotationY", this, &ABCPlayerController::OnRotateY);

    // Fire Primary Weapon Button Bindings
    InputComponent->BindAction("FirePrimaryWeapon", IE_Pressed, this, &ABCPlayerController::OnBeginFirePrimary);
    InputComponent->BindAction("FirePrimaryWeapon", IE_Released, this, &ABCPlayerController::OnEndFirePrimary);
}

void ABCPlayerController::OnMoveForward(float Value)
{
    APawn* const Pawn = GetPawn();

    if ((Value != 0.0f) && Pawn) {
        // find out which way is forward
        FRotator Rotation = GetControlRotation();
        // Limit pitch when walking or falling

        // add movement in that direction
        const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
        Pawn->AddMovementInput(Direction, Value);
    }
}

void ABCPlayerController::OnMoveRight(float Value)
{

    APawn* const Pawn = GetPawn();

    if ((Value != 0.0f) && Pawn) {
        // find out which way is forward
        FRotator Rotation = GetControlRotation();
        // Limit pitch when walking or falling

        // add movement in that direction
        const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
        Pawn->AddMovementInput(Direction, Value);
    }
}

void ABCPlayerController::OnRotateX(float Value)
{
    APawn* const Pawn = GetPawn();

    if ((Value != 0.0f) && Pawn) {
        storedRotationX = Value;
    }
}

void ABCPlayerController::OnRotateY(float Value)
{
    APawn* const Pawn = GetPawn();

    if ((Value != 0.0f) && Pawn) {
        storedRotationY = Value;
    }
}

void ABCPlayerController::OnBeginFirePrimary()
{
    // TODO: Add FirePrimaryWeapon Begin Functionality
}

void ABCPlayerController::OnEndFirePrimary()
{
    // TODO: Add FirePrimaryWeapon End Functionality
}
