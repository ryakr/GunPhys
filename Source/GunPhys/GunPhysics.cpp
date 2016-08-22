// Fill out your copyright notice in the Description page of Project Settings.

#include "GunPhys.h"
#include "Kismet/KismetMathLibrary.h"
#include "GunPhysics.h"
#include "Components/ArrowComponent.h"
#include "Components/InputComponent.h"
#include "Animation/AnimInstance.h"

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
	Held = false;
	EnviromentTemprature = 70;
	BarrelDamage = 0;
	DamagePoint = 300;
	CoolingConstant = 0.01771;
	CoolingConstantNewMag = 0.03771;
	RunningCoolMag = false;
	MagTemprature = 70;
	bulletspermag = 17;
	lay_mo = 17;
	magazines = 0; 
}

void UGunPhysics::ChamberCheckPressed(UAnimInstance* Arms, UAnimInstance* Gun, UAnimMontage* Arm_Animation, UAnimMontage* Gun_Animation, float pausetime, UStaticMeshComponent* Shell)
{
	FTimerDelegate ChamberDel;
	if (lay_mo == 0) {
		if (Shell == NULL) {
			UE_LOG(LogStreaming, Log,
				TEXT("Shell Not Defined In BP"));
		}
		Shell->SetVisibility(false);
	}
	Held = true;
	Arms->Montage_Play(Arm_Animation);
	Gun->Montage_Play(Gun_Animation);
	ChamberDel.BindUFunction(this, FName("PauseChamberCheck"), Arms, Gun, Arm_Animation, Gun_Animation);
	GetWorld()->GetTimerManager().SetTimer(MontageTick, ChamberDel, pausetime, false);
	return;
}

void UGunPhysics::ChamberCheckReleased(UAnimInstance* Arms, UAnimInstance* Gun, UAnimMontage* Arm_Animation, UAnimMontage* Gun_Animation)
{
	Held = false;
	Arms->Montage_Resume(Arm_Animation);
	Gun->Montage_Resume(Gun_Animation);
	return;
}

void UGunPhysics::PauseChamberCheck(UAnimInstance* Arms, UAnimInstance* Gun, UAnimMontage* Arm_Animation, UAnimMontage* Gun_Animation)
{
	if (Held) 
	{
		Arms->Montage_Pause(Arm_Animation);
		Gun->Montage_Pause(Gun_Animation);

		if (!Held)
		{
			Arms->Montage_Resume(Arm_Animation);
			Gun->Montage_Resume(Gun_Animation);
			GetWorld()->GetTimerManager().ClearTimer(MontageTick);
			return;
		}
		GetWorld()->GetTimerManager().ClearTimer(MontageTick);
		return;
	}
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
	GetWorld()->GetTimerManager().ClearTimer(MontageTick);
}
void UGunPhysics::testing(bool test)
{
	return;
}
void UGunPhysics::Jam()
{
	if (UKismetMathLibrary::RandomIntegerInRange(1, (1000 / BarrelDamage)) == 5) {
		if (UKismetMathLibrary::RandomIntegerInRange(1, 2) == 1) {
			Jam_FTF = true;
			Jammed = true;
			return;
		}
		else {
			Jam_Stovepipe = true;
			Jammed = true;
			return;
		}
	}
	else if (UKismetMathLibrary::RandomIntegerInRange(1, (1500 / BarrelDamage)) == 5) {
		if (UKismetMathLibrary::RandomIntegerInRange(1, 2) == 1) {
			Jam_HangFire = true;
			Jammed = true;
			return;
		}
		else {
			Jam_Squib = true;
			Jammed = true;
			return;
		}
	}
}
bool UGunPhysics::Shot()
{
	if (lay_mo > 0) {
		lay_mo -= 1;
		if (GunTemprature >= 199.68 && bShouldCountTemp) {
			float heatcoe = 0.2;
			GunTemprature += pow(199.68, heatcoe);
			Jam();
			return true;
		}
		if (GunTemprature <= 199.68 && bShouldCountTemp) {
			GunTemprature += UKismetMathLibrary::RandomFloatInRange(1, 5) + pow(GunTemprature, 0.3);
			
			if (GunTemprature <= 150) {
				GunTemprature += UKismetMathLibrary::RandomFloatInRange(1, 5) + pow(GunTemprature, 0.3);
				
				if (GunTemprature <= 100) {
					GunTemprature += UKismetMathLibrary::RandomFloatInRange(1, 5) + pow(GunTemprature, 0.4);
					return true;
				}
			return true;
			}
		return true;
		}
		return true;
	}
	else {
		return false;
	}
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
void UGunPhysics::NewMag(UStaticMeshComponent* Shell)
{
	if (magazines > 0)
	{
		if (!Shell) {
			UE_LOG(LogStreaming, Log,
				TEXT("Shell Not Defined In BP"));
		}
		FTimerDelegate ReloadDel;
		ReloadDel.BindUFunction(this, FName("AddHeat"), Shell);
		GetWorld()->GetTimerManager().SetTimer(MagTick, ReloadDel, 1.5f, false);
		return;
	}
	return;
}
void UGunPhysics::AddHeat(UStaticMeshComponent* Shell)
{
	magazines -= 1;
	lay_mo = bulletspermag;
	Shell->SetVisibility(true);
	MagTemprature = EnviromentTemprature;
	GetWorld()->GetTimerManager().ClearTimer(MagTick);
	if (MagTemprature == GunTemprature) {
		RunningCoolMag = false;
		return;
	}
	else {
		RunningCoolMag = true;
		return;
	}
}
void UGunPhysics::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	//cooling function begin
	Time = DeltaTime + Time;
	if (Time >= 1 && bShouldCountTemp) {
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
		if (GunTemprature < EnviromentTemprature) {
			float dt = EnviromentTemprature - GunTemprature;
			float btu = 1.08 * (dt); //btu = 242 cal = 1012528 joules = 533.161883743966 C/hr = 991.6913907391387966 F/hr
				btu /= 3600;
				btu *= 242;
				btu *= 4184;
				btu /= 1899.1005;
				btu = btu * 1.8 + 32;
				// hs = 1.08 q dt
				//hs = sensible heat(Btu / hr)
				//q = air volume flow(cfm, cubic feet per minute)
				//dt = temperature difference(oF)
				GunTemprature += btu;
		}
			
	}
	//cooling function end
	if (GunTemprature >= DamagePoint && bShouldCountTemp)
	{
		BarrelDamage += 0.0005;
	}
}

