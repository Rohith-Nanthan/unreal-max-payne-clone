// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCombatHandler.generated.h"

class UMaxPayneCameraMover;
class UPlayerInputReaderComponent;
class UWeaponShootComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UPlayerCombatHandler : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerCombatHandler();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void Initialize(UPlayerInputReaderComponent* InputReader, UMaxPayneCameraMover* CameraMover,
	                UWeaponShootComponent* WeaponShootComponent);
	void Shoot();

private:
	void HandleCameraFocusingForNormalShoot(float DeltaTime);
	void HandleCameraFocusForADS();

private:
	UPROPERTY()
	TObjectPtr<UMaxPayneCameraMover> CameraMover;

	UPROPERTY()
	TObjectPtr<UPlayerInputReaderComponent> InputReader;

	UPROPERTY()
	TObjectPtr<UWeaponShootComponent> WeaponShoot;

	UPROPERTY(EditAnywhere)
	float ShootCameraFocusDuration = 3.f;

	float ElapsedCameraFocusTimeForNormalShoot;
	bool bIsCameraFocusingForNormalShoot;
	bool bIsCameraAimingPreviousFrame;

	void CheckAndFocusCameraForShoot();
};
