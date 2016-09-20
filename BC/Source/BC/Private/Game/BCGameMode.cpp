// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "BC.h"
#include "BCGameMode.h"
#include "BC/Public/UI/BCHUD.h"
#include "BCPlayerController.h"
#include "BCCharacter.h"

ABCGameMode::ABCGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ABCPlayerController::StaticClass();

	// use our custom HUD class
	HUDClass = ABCHUD::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}