// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Editor/PropertyEditorTestObject.h"
#include "MaxPayneCameraMover.generated.h"

UENUM()
enum ECameraFocusMode
{
	ECFM_NoShoot,
	ECFM_NormalShoot,
	ECFM_ADS_Shoot,
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
	UPROPERTY(EditAnywhere)
	float CameraLerpSpeedForFocusChange = 2.f;

	UPROPERTY(EditAnywhere)
	float CameraLerpEaseSpeedExponential = 1.f;

	UPROPERTY(VisibleAnywhere)
	bool bIsUpdatingCameraPosition;
	
	UPROPERTY(VisibleAnywhere)
	FVector StartingCameraPosition;

	UPROPERTY(VisibleAnywhere)
	FVector DesiredCameraPosition;

	UPROPERTY(VisibleAnywhere)
	float LerpProgress;
	
	void UpdateCameraPositionForFocusMode(float DeltaTime);

protected:
	UPROPERTY(EditAnywhere)
	FVector NoShootCameraOffset;

	UPROPERTY(EditAnywhere)
	FVector NormalShootCameraOffset;

	UPROPERTY(EditAnywhere)
	FVector ADS_ShootCameraOffset;

private:
	UPROPERTY()
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY()
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY()
	TObjectPtr<AMaxPayneController> MaxPayneController;

	UPROPERTY(VisibleAnywhere)
	TEnumAsByte<ECameraFocusMode> CurrentCameraFocusMode;
};
