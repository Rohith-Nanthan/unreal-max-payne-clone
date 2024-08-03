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
	if (bIsCameraAimingPreviousFrame || !bIsCameraFocusingForNormalShoot)
	{
		return;
	}

	ElapsedCameraFocusTimeForNormalShoot += DeltaTime;
	if (ElapsedCameraFocusTimeForNormalShoot > ShootCameraFocusDuration)
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

	const bool bIsCameraAimingCurrentFrame = InputReader->bIsAiming;

	if (bIsCameraAimingPreviousFrame == bIsCameraAimingCurrentFrame)
	{
		return;
	}

	if (bIsCameraAimingCurrentFrame)
	{
		if (CameraMover)
		{
			CameraMover->SwitchCameraFocusMode(ECameraFocusMode::ECFM_ADS_Shoot);
		}
	}
	else
	{
		if (CameraMover)
		{
			CameraMover->SwitchCameraFocusMode(ECameraFocusMode::ECFM_NoShoot);
		}
	}
	
	bIsCameraAimingPreviousFrame = bIsCameraAimingCurrentFrame;
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
	if (bIsCameraAimingPreviousFrame)
	{
		return;
	}

	ElapsedCameraFocusTimeForNormalShoot = 0;
	if (bIsCameraFocusingForNormalShoot)
	{
		return;
	}

	bIsCameraFocusingForNormalShoot = true;
	if (CameraMover)
	{
		CameraMover->SwitchCameraFocusMode(ECameraFocusMode::ECFM_NormalShoot);
	}
}

void UPlayerCombatHandler::Shoot()
{
	WeaponShoot->Shoot();
	CheckAndFocusCameraForShoot();
}
