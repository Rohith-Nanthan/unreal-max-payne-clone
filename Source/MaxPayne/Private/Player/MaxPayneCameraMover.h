// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/FSM.h"
#include "Editor/PropertyEditorTestObject.h"
#include "MaxPayneCameraMover.generated.h"

UENUM()
enum ECameraFocusMode
{
	ECFM_NoShoot,
	ECFM_NormalShoot,
	ECFM_ADS_Shoot,
};

USTRUCT()
struct FCameraOffsetData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FVector CameraOffset;

	UPROPERTY(EditAnywhere)
	float CameraLerpSpeed;

	UPROPERTY(EditAnywhere)
	float CameraLerpSpeedEaseExponential;
};

class USpringArmComponent;
class UCameraComponent;
class AMaxPayneController;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UMaxPayneCameraMover : public UActorComponent
{
	GENERATED_BODY()

public:
	UMaxPayneCameraMover();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void Initialize(USpringArmComponent* SpringArmComponentToSet, UCameraComponent* CameraComponentToSet,
	                AMaxPayneController* MaxPayneControllerToSet);
	void SwitchCameraFocusMode(ECameraFocusMode NewFocusMode);

private:
	UPROPERTY(VisibleAnywhere)
	bool bIsUpdatingCameraPosition;

	UPROPERTY(VisibleAnywhere)
	FVector StartingCameraPosition;

	UPROPERTY(VisibleAnywhere)
	float LerpProgress;

	void UpdateCameraPositionForFocusMode(float DeltaTime);

protected:
	UPROPERTY(EditAnywhere)
	FCameraOffsetData NoShootCameraOffset =
	{
		FVector(0.f, 50.f, 0.f),
		2.f,
		3.f
	};

	UPROPERTY(EditAnywhere)
	FCameraOffsetData NormalShootCameraOffset =
	{
		FVector(10.f, 100.f, 0.f),
		2.f,
		3.f
	};

	UPROPERTY(EditAnywhere)
	FCameraOffsetData ADS_ShootCameraOffset =
	{
		FVector(80.f, 50.f, 0.f),
		5.f,
		3.f
	};

private:
	UPROPERTY()
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY()
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY()
	TObjectPtr<AMaxPayneController> MaxPayneController;

	Create_FSM(CameraFocus_FSM, ECameraFocusMode,UMaxPayneCameraMover)
	CameraFocus_FSM<ECameraFocusMode>* FocusMode_FSM;
	
	FCameraOffsetData* DesiredCameraOffset;

	bool SwitchCameraFocusState(CameraFocus_FSM<ECameraFocusMode>& FSM_Inst, ECameraFocusMode NewFocusMode)
	{
		return  FSM_Inst.SwitchState(NewFocusMode);
	}
};

