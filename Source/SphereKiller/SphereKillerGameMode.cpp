// Copyright Epic Games, Inc. All Rights Reserved.

#include "SphereKillerGameMode.h"
#include "SphereKillerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASphereKillerGameMode::ASphereKillerGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
