// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MaxPayneCameraMover.h"

#include "MaxPayneController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

UMaxPayneCameraMover::UMaxPayneCameraMover()
{
	CurrentCameraFocusMode = ECFM_NoShoot;
	PrimaryComponentTick.bCanEverTick = true;
}

void UMaxPayneCameraMover::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (MaxPayneController && SpringArmComponent)
	{
		SpringArmComponent->SetWorldRotation(MaxPayneController->LookRotator);
	}

	UpdateCameraPositionForFocusMode(DeltaTime);
}

void UMaxPayneCameraMover::Initialize(USpringArmComponent* SpringArmComponentToSet,
                                      UCameraComponent* CameraComponentToSet,
                                      AMaxPayneController* MaxPayneControllerToSet)
{
	SpringArmComponent = SpringArmComponentToSet;
	CameraComponent = CameraComponentToSet;
	MaxPayneController = MaxPayneControllerToSet;
	if (!MaxPayneController)
	{
		UE_LOG(LogTemp, Error, TEXT("Controller is not AMaxPayneController"));
	}

	if (CameraComponent)
	{
		CameraComponent->SetRelativeLocation(NoShootCameraOffset.CameraOffset);
	}
}

void UMaxPayneCameraMover::SwitchCameraFocusMode(ECameraFocusMode NewFocusMode)
{
	if (CurrentCameraFocusMode == NewFocusMode)
	{
		return;
	}

	CurrentCameraFocusMode = NewFocusMode;
	switch (CurrentCameraFocusMode)
	{
	case ECFM_NoShoot:
		DesiredCameraOffset = &NoShootCameraOffset;
		break;

	case ECFM_NormalShoot:
		DesiredCameraOffset = &NormalShootCameraOffset;
		break;

	case ECFM_ADS_Shoot:
		DesiredCameraOffset = &ADS_ShootCameraOffset;
		break;

	default:
		UE_LOG(LogTemp, Error, TEXT("Camera focus mode not found"));
		break;
	}

	bIsUpdatingCameraPosition = true;
	LerpProgress = 0.f;
	if (CameraComponent)
	{
		StartingCameraPosition = CameraComponent->GetRelativeLocation();
	}
}

void UMaxPayneCameraMover::UpdateCameraPositionForFocusMode(float DeltaTime)
{
	if (!CameraComponent || !bIsUpdatingCameraPosition)
	{
		return;
	}

	if (LerpProgress >= 1)
	{
		LerpProgress = 1;
		bIsUpdatingCameraPosition = false;
		return;
	}

	LerpProgress += DeltaTime * DesiredCameraOffset->CameraLerpSpeed;
	const FVector DeltaCameraPosition = FMath::InterpEaseOut(StartingCameraPosition,
	                                                         DesiredCameraOffset->CameraOffset, LerpProgress,
	                                                         DesiredCameraOffset->CameraLerpSpeedEaseExponential);
	CameraComponent->SetRelativeLocation(DeltaCameraPosition);
}
