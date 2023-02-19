// Copyright Epic Games, Inc. All Rights Reserved.

#include "RealisticMovementGameMode.h"
#include "RealisticMovementCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARealisticMovementGameMode::ARealisticMovementGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
