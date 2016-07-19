// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "GunPhys.h"
#include "GunPhysGameMode.h"
#include "GunPhysHUD.h"
#include "GunPhysCharacter.h"

AGunPhysGameMode::AGunPhysGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonBPIronbelly/Blueprints/FirstPersonCharacterIronbelly"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
