// Copyright Epic Games, Inc. All Rights Reserved.

#include "OPYEGameMode.h"
#include "OPYECharacter.h"
#include "UObject/ConstructorHelpers.h"

AOPYEGameMode::AOPYEGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
