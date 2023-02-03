// Copyright Epic Games, Inc. All Rights Reserved.

#include "GGJ2023GameMode.h"
#include "GGJ2023Character.h"
#include "UObject/ConstructorHelpers.h"

AGGJ2023GameMode::AGGJ2023GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
