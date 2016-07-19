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
	if (Time >= 1) {
		Time -= Time;
		if (GunTemprature > EnviromentTemprature) {
			GunTemprature -= UKismetMathLibrary::RandomFloatInRange(0.5, 1.67);
		}
	}
	//cooling function end
	if (GunTemprature >= 300)
	{
		BarrelDamage += 0.0005;
	}
}

