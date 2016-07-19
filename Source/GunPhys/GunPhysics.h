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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float GunTemprature;
	//Changable Area Temprature
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float EnviromentTemprature;
	//The Point Where Problems Begin
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float MaxTemp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float BarrelDamage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ProjectileBounces)
	uint32 bShouldCountTemp : 1;

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		float Time;
};
