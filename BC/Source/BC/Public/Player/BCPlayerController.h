// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "BCPlayerController.generated.h"

UCLASS()
class ABCPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABCPlayerController();

protected:
	
	/** Stored rotation values */
	float storedRotationX;
	float storedRotationY;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Input handlers for Movement action */
	void OnMoveForward(float Value);
	void OnMoveRight(float Value);

	/** Input handlers for Rotation action */
	void OnRotateX(float Value);
	void OnRotateY(float Value);
};


