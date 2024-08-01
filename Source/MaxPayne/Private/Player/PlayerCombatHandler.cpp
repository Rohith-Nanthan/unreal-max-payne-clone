// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCombatHandler.h"

#include "MaxPayneCameraMover.h"
#include "PlayerInputReaderComponent.h"
#include "Combat/WeaponShootComponent.h"

UPlayerCombatHandler::UPlayerCombatHandler()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerCombatHandler::HandleCameraFocusingForNormalShoot(float DeltaTime)
{
	if (!bIsCameraFocusingForNormalShoot)
	{
		return;
	}

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

void UPlayerCombatHandler::HandleCameraFocusForADS()
{
	if (!InputReader)
	{
		return;
	}

	const bool bIsCameraAimingNow = InputReader->bIsAiming;
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

// Called every frame
void UPlayerCombatHandler::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HandleCameraFocusForADS();
	HandleCameraFocusingForNormalShoot(DeltaTime);
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
	if (bIsCameraAiming)
	{
		return;
	}

	if (bIsCameraFocusingForNormalShoot)
	{
		ElapsedCameraFocusTime = 0;
		return;
	}

	if (CameraMover)
	{
		CameraMover->SwitchCameraFocusMode(ECameraFocusMode::ECFM_NormalShoot);
	}
	bIsCameraFocusingForNormalShoot = true;
	ElapsedCameraFocusTime = 0;
}

void UPlayerCombatHandler::Shoot()
{
	WeaponShoot->Shoot();
	CheckAndFocusCameraForShoot();
}
