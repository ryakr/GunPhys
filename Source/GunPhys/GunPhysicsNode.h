// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GunPhys.h"
#include "GunPhysics.h"
#include "GunPhysicsNode.generated.h"
/**
 * 
 */
UCLASS()
class GUNPHYS_API UGunPhysicsNode : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Heat To Barrel (Deprecated) ", Keywords = "Angle Between Vectors"), Category = "Bullet Physics")
		static bool Shot(UGunPhysics* GunComponent);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Accuracy (Deprecated)", Keywords = "Angle Between Vectors"), Category = "Bullet Physics")
		static float Accuracy(UGunPhysics* GunComponent, UArrowComponent* FireArrow);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MathTester (Deprecated)", Keywords = "Angle Between Vectors"), Category = "Bullet Physics")
		static float MathTester(UGunPhysics* GunComponent);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "New Mag (Deprecated)", Keywords = "Angle Between Vectors"), Category = "Bullet Physics")
		static bool NewMag(UGunPhysics* GunComponent);
};
