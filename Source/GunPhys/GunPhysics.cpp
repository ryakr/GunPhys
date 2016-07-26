// Fill out your copyright notice in the Description page of Project Settings.

#include "GunPhys.h"
#include "Kismet/KismetMathLibrary.h"
#include "GunPhysics.h"
#include "Components/ArrowComponent.h"

// Sets default values for this component's properties
UGunPhysics::UGunPhysics()
{
	
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	//Start Gun Temp
	GunTemprature = 70;
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
	MagTemprature = 70;
}


// Called when the game starts
void UGunPhysics::BeginPlay()
{
	Super::BeginPlay();
	
}
void UGunPhysics::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Ensure the MagTick timer is cleared
	GetWorld()->GetTimerManager().ClearTimer(MagTick);

}
void UGunPhysics::testing(bool test)
{
	return;
}
void UGunPhysics::Shot()
{
	float heatcoe = 0.2;
	if (GunTemprature <= EnviromentTemprature && bShouldCountTemp == true)
	{
		GunTemprature = UKismetMathLibrary::RandomFloatInRange(0.5, 2) + 199.68;
		return;
	}
	if (GunTemprature >= 199.68 && bShouldCountTemp) {
		GunTemprature += pow(199.68, heatcoe);
		return;
	}
	if (GunTemprature <= 199.68 && bShouldCountTemp) {
		GunTemprature += UKismetMathLibrary::RandomFloatInRange(1, 5) + pow(GunTemprature, 0.3);
		return;
		if (GunTemprature <= 150) {
			GunTemprature += UKismetMathLibrary::RandomFloatInRange(1, 5) + pow(GunTemprature, 0.3);
			return;
			if (GunTemprature <= 100) {
				GunTemprature += UKismetMathLibrary::RandomFloatInRange(1, 5) + pow(GunTemprature, 0.4);
				return;
			}
		}
	}
	return;
}
void UGunPhysics::Accuracy(UArrowComponent* FireArrow)
{
	FRotator Default = UKismetMathLibrary::MakeRotator(0, 0, 90);
	float random = UKismetMathLibrary::RandomFloatInRange(0, 0.5);
	if (GunTemprature >= 200) {
		if (random >= 0.4) {
			float pitch = UKismetMathLibrary::RandomFloatInRange(-0.5, 0.5);
			float yaw = UKismetMathLibrary::RandomFloatInRange(-0.5, 0.5);
			pitch += (GunTemprature * 0.005);
			yaw += (GunTemprature * 0.005);
			FireArrow->AddRelativeRotation(UKismetMathLibrary::MakeRotator(0, pitch, yaw));
			return;
		}
		else {
			FireArrow->SetRelativeRotation(Default);
			return;
		}
	}
	else {
		FireArrow->SetRelativeRotation(Default);
		return;
	}

}
void UGunPhysics::NewMag()
{
	GetWorld()->GetTimerManager().SetTimer(MagTick, this, &UGunPhysics::AddHeat, 1.5f, false);
	return;
}
void UGunPhysics::AddHeat()
{
	MagTemprature = EnviromentTemprature;
	if (MagTemprature == GunTemprature) {
		RunningCoolMag = false;
		GetWorld()->GetTimerManager().ClearTimer(MagTick);
		return;
	}
	else {
		RunningCoolMag = true;
		GetWorld()->GetTimerManager().ClearTimer(MagTick);
		return;
	}
}
void UGunPhysics::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	//cooling function begin
	Time = DeltaTime + Time;
	if (Time >= 1 && bShouldCountTemp == true) {
		Time -= Time;
		if (GunTemprature > EnviromentTemprature && !RunningCoolMag) {
			float answer2 = exp(-(CoolingConstant * 1));
			GunTemprature = EnviromentTemprature + (GunTemprature - EnviromentTemprature) * answer2;
		}
		if (GunTemprature > EnviromentTemprature && RunningCoolMag) {
			float answer2 = exp(-(CoolingConstantNewMag * 1));
			GunTemprature = EnviromentTemprature + (GunTemprature - EnviromentTemprature) * answer2;
		}
		if (MagTemprature < (GunTemprature - 1)) {
			MagTemprature += pow((GunTemprature - MagTemprature), 0.5);
		}
		else if (MagTemprature > (GunTemprature + 1)) {
			MagTemprature -= pow((MagTemprature - GunTemprature), 0.2);
		}
		else if (MagTemprature < (GunTemprature + 1) && (MagTemprature > (MagTemprature - 1))) {
			RunningCoolMag = false;
		}
	}
	//cooling function end
	if (GunTemprature >= DamagePoint && bShouldCountTemp == true)
	{
		BarrelDamage += 0.0005;
	}
}

