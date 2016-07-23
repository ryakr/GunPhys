// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "GunPhysics.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GUNPHYS_API UGunPhysics : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGunPhysics();


	//Temprature of Barrel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponPhysics)
	float GunTemprature;
	//Temprature of the Magazine
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponPhysics)
		float MagTemprature;
	//Changable Area Temprature
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponPhysics)
	float EnviromentTemprature;
	//Max Gun Temprature
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponPhysics)
	float MaxTemp;
	//Temprature Where Barrel Damage Slowly Occurs. Called Every Tick
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponPhysics)
	float DamagePoint;
	//1-100, amount of damage to the barrel of the gun
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponPhysics)
	float BarrelDamage;
	//1-100, amount of damage to the barrel of the gun
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponPhysics)
		float CoolingConstant;
	//Gun cools faster with new mag, adjust accordingly
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponPhysics)
		float CoolingConstantNewMag;
	//true if the gun is running a cold mag
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponPhysics)
		bool RunningCoolMag;
	//should temprature be counted, or stay and the default setting?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponPhysics)
	uint32 bShouldCountTemp : 1;

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		float Time;
};
