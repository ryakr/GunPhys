// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "GunPhysHUD.generated.h"

UCLASS()
class AGunPhysHUD : public AHUD
{
	GENERATED_BODY()



private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

