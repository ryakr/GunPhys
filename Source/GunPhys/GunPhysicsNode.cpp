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
	float heatcoe = 0.2;
	if (Temperatur <= GunComponent->EnviromentTemprature && GunComponent->bShouldCountTemp == true)
	{
		GunComponent->GunTemprature = UKismetMathLibrary::RandomFloatInRange(0.5, 2) + 199.68;
		return true;
	}
	if (Temperatur >= 199.68 && GunComponent->bShouldCountTemp == true) {
		GunComponent->GunTemprature = Temperatur + pow(199.68, heatcoe);
		return true;
	}
	if (Temperatur <= 199.68 && GunComponent->bShouldCountTemp == true) {
		GunComponent->GunTemprature = Temperatur + UKismetMathLibrary::RandomFloatInRange(1, 5) + pow(Temperatur, 0.3);
		return true;
		if (Temperatur <= 150) {
			GunComponent->GunTemprature = Temperatur + UKismetMathLibrary::RandomFloatInRange(1, 5) + pow(Temperatur, 0.3);
			return true;
			if (Temperatur <= 100) {
				GunComponent->GunTemprature = Temperatur + UKismetMathLibrary::RandomFloatInRange(1, 5) + pow(Temperatur, 0.4);
				return true;
			}
		}
	}
	return false;
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
float UGunPhysicsNode::MathTester(
	UGunPhysics* GunComponent
	) {
	float Enviroment = GunComponent->EnviromentTemprature;
	float answer2 = exp(-(GunComponent->CoolingConstant * 1));
	float answer = Enviroment + (GunComponent->GunTemprature - Enviroment) * answer2;
	return answer;
}
bool UGunPhysicsNode::NewMag(
	UGunPhysics* GunComponent
	) {
	GunComponent->MagTemprature = GunComponent->EnviromentTemprature;
	if (GunComponent->MagTemprature == GunComponent->GunTemprature) {
		GunComponent->RunningCoolMag = false;
		return GunComponent->RunningCoolMag;
	} else {
		GunComponent->RunningCoolMag = true;
	return GunComponent->RunningCoolMag;
}
}