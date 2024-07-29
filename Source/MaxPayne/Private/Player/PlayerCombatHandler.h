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
	// Sets default values for this component's properties
	UPlayerCombatHandler();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void Initialize(UPlayerInputReaderComponent* InputReader, UMaxPayneCameraMover* CameraMover,
	                UWeaponShootComponent* WeaponShootComponent);
	void Shoot();
	
private:
	UPROPERTY()
	TObjectPtr<UMaxPayneCameraMover> CameraMover;

	UPROPERTY()
	TObjectPtr<UPlayerInputReaderComponent> InputReader;

	UPROPERTY()
	TObjectPtr<UWeaponShootComponent> WeaponShoot;

	UPROPERTY(EditAnywhere)
	float ShootCameraFocusDuration;

	float ElapsedCameraFocusTime;
	bool bIsCameraFocusingForNormalShoot;
	bool bIsCameraAiming;
	
	void CheckAndFocusCameraForShoot();
};
