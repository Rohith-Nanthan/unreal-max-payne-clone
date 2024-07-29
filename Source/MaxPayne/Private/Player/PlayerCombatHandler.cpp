// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCombatHandler.h"

#include "MaxPayneCameraMover.h"
#include "PlayerInputReaderComponent.h"
#include "Combat/WeaponShootComponent.h"

// Sets default values for this component's properties
UPlayerCombatHandler::UPlayerCombatHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerCombatHandler::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UPlayerCombatHandler::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool bIsCameraAimingNow = InputReader->bIsAiming;
	if (InputReader)
	{
		if (!bIsCameraAiming && bIsCameraAimingNow)
		{
			bIsCameraAiming = true;
			if (CameraMover)
			{
				CameraMover->SwitchCameraFocusMode(ECameraFocusMode::ECFM_ADS_Shoot);
			}
		}
		else if (bIsCameraAiming && !bIsCameraAimingNow)
		{
			bIsCameraAiming = false;
			CheckAndFocusCameraForShoot();
		}
	}

	if (bIsCameraFocusingForNormalShoot)
	{
		ElapsedCameraFocusTime += DeltaTime;
		if (ElapsedCameraFocusTime > ShootCameraFocusDuration)
		{
			bIsCameraFocusingForNormalShoot = false;

			if (CameraMover)
			{
				CameraMover->SwitchCameraFocusMode(ECameraFocusMode::ECFM_NoShoot);
			}
		}
	}
}

void UPlayerCombatHandler::Initialize(UPlayerInputReaderComponent* InputReaderComponent,
                                      UMaxPayneCameraMover* CameraMoverComponent,
                                      UWeaponShootComponent* WeaponShootComponent)
{
	InputReader = InputReaderComponent;
	CameraMover = CameraMoverComponent;
	WeaponShoot = WeaponShootComponent;
}

void UPlayerCombatHandler::CheckAndFocusCameraForShoot()
{
	if (!bIsCameraAiming && !bIsCameraFocusingForNormalShoot)
	{
		if (CameraMover)
		{
			CameraMover->SwitchCameraFocusMode(ECameraFocusMode::ECFM_NormalShoot);
		}
		bIsCameraFocusingForNormalShoot = true;
		ElapsedCameraFocusTime = 0;
	}
}

void UPlayerCombatHandler::Shoot()
{
	WeaponShoot->Shoot();
	CheckAndFocusCameraForShoot();
}
