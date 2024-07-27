// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MaxPayneController.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "MaxPayneCharacter.generated.h"

class UCapsuleComponent;
class UPlayerMovementComponent;
class USpringArmComponent;
class UCameraComponent;
class UHealthComponent;
class UWeaponShootComponent;
class AMaxPayneController;

UCLASS()
class AMaxPayneCharacter : public APawn
{
	GENERATED_BODY()

public:
	AMaxPayneCharacter();

private:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> CapsuleCollider;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UPlayerMovementComponent> PlayerMover;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UWeaponShootComponent> WeaponShootComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AMaxPayneController> MaxPayneController;

public:
	void Shoot();
};

