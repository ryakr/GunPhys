// Fill out your copyright notice in the Description page of Project Settings.

#include "GunPhys.h"
#include "GunPhysicsNode.h"
#include "GunPhysics.h"
#include "Components/SceneComponent.h"
#include "Engine.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include <string>

UGunPhysicsNode::UGunPhysicsNode(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	
}
bool UGunPhysicsNode::Shot(
	UGunPhysics* GunComponent
	) {
	float Temperatur = GunComponent->GunTemprature;
	float limit = GunComponent->MaxTemp;
	float NewHeat = UKismetMathLibrary::RandomFloatInRange(0.5, 2) + Temperatur;
	GunComponent->GunTemprature = NewHeat;
	if (Temperatur >= limit)
	{
		return false;
	} else {
		return true;
	}

}

float UGunPhysicsNode::Accuracy(
	UGunPhysics* GunComponent, 
	UArrowComponent* FireArrow
	) {
	FRotator Default = UKismetMathLibrary::MakeRotator(0, 0, 90);
	float random = UKismetMathLibrary::RandomFloatInRange(0, 0.5);
	if (GunComponent->GunTemprature >= 200) {
		if (random >= 0.4) {
			float pitch = UKismetMathLibrary::RandomFloatInRange(-0.5, 0.5);
			float yaw = UKismetMathLibrary::RandomFloatInRange(-0.5, 0.5);
			pitch += (GunComponent->GunTemprature * 0.005);
			yaw += (GunComponent->GunTemprature * 0.005);
			FireArrow->AddRelativeRotation(UKismetMathLibrary::MakeRotator(0, pitch, yaw));
			return random;
		}
		else {
			FireArrow->SetRelativeRotation(Default);
			return random;
		}
	} else {
		FireArrow->SetRelativeRotation(Default);
		return random;
	}

}