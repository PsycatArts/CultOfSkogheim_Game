// Copyright Epic Games, Inc. All Rights Reserved.

#include "SkogheimGameMode.h"
#include "SkogheimCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASkogheimGameMode::ASkogheimGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
