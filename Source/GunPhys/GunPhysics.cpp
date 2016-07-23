// Fill out your copyright notice in the Description page of Project Settings.

#include "GunPhys.h"
#include "Kismet/KismetMathLibrary.h"
#include "GunPhysics.h"


// Sets default values for this component's properties
UGunPhysics::UGunPhysics()
{
	
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	//Start Gun Temp
	GunTemprature = 0;
	//600F = Max Temp
	MaxTemp = 600;
	//By Default Temp Affects Weapon
	bShouldCountTemp = true;
	bAutoActivate = true;
	Time = 0;
	EnviromentTemprature = 70;
	BarrelDamage = 0;
	DamagePoint = 300;
	CoolingConstant = 0.01771;
	CoolingConstantNewMag = 0.03771;
	RunningCoolMag = false;
	MagTemprature = 0;
}


// Called when the game starts
void UGunPhysics::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame

void UGunPhysics::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	//cooling function begin
	Time = DeltaTime + Time;
	if (Time >= 1 && bShouldCountTemp == true) {
		Time -= Time;
		if (GunTemprature > EnviromentTemprature && RunningCoolMag== false) {
			float answer2 = exp(-(CoolingConstant * 1));
			GunTemprature = EnviromentTemprature + (GunTemprature - EnviromentTemprature) * answer2;
		}
		if (GunTemprature > EnviromentTemprature && RunningCoolMag == true) {
			float answer2 = exp(-(CoolingConstantNewMag * 1));
			GunTemprature = EnviromentTemprature + (GunTemprature - EnviromentTemprature) * answer2;
		}
		if (MagTemprature < GunTemprature) {
			MagTemprature += pow((GunTemprature - MagTemprature), 0.5);
		}
		if (MagTemprature > GunTemprature) {
			MagTemprature -= pow((MagTemprature - GunTemprature), 0.2);
		}
		if (MagTemprature == GunTemprature) {
			RunningCoolMag = false;
		}
	}
	//cooling function end
	if (GunTemprature >= DamagePoint && bShouldCountTemp == true)
	{
		BarrelDamage += 0.0005;
	}
}

