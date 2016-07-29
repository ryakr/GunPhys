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
	//Cooling Constant Of the Metal
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
	//bool checked to see if the gun has been Jammed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponPhysics)
		bool Jammed;
	//dud or delayed firing of round: wait 30 seconds then remove round
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponPhysics)
		bool Jam_HangFire;
	//Bullet stuck in barrel: Slide object into hole to not scratch the outside
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponPhysics)
		bool Jam_Squib;
	//Shell Not Ejected: Remove Mag and drop shell through Mag Hole
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponPhysics)
		bool Jam_FTF;
	//Shell Half Ejected: Remove Mag and pull back slide
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponPhysics)
		bool Jam_Stovepipe;
	//tick for seting the mag temp
	UPROPERTY()
		FTimerHandle MagTick;
	// Called when the game starts
	virtual void BeginPlay() override;
	//EndPlay Reset
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Test")
		virtual void testing(bool test);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Heat To Barrel", Keywords = "Add Heat To Barrel"), Category = "Gun Physics")
		virtual void Shot();
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Accuracy", Keywords = "Accuracy"), Category = "Gun Physics")
		virtual void Accuracy(UArrowComponent* FireArrow);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "New Mag", Keywords = "New Mag"), Category = "Gun Physics")
		virtual void NewMag();
	UFUNCTION(meta = (DisplayName = "New Mag", Keywords = "New Mag"), Category = "Gun Physics")
		virtual void AddHeat();
	UFUNCTION(meta = (DisplayName = "New Mag", Keywords = "New Mag"), Category = "Gun Physics")
		virtual void Jam();
	UPROPERTY(EditAnywhere)
		float Time;
};
