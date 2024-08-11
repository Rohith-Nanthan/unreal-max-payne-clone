// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "MaxPayneCharacter.generated.h"

class UCapsuleComponent;
class UPlayerMovementComponent;
class USpringArmComponent;
class UCameraComponent;
class UHealthComponent;
class APistolWeapon;
class UMaxPayneCameraMover;
class UMaxPayneAnimationHandler;
class UPlayerCombatHandler;
class UPlayerHUD;

UCLASS()
class AMaxPayneCharacter : public APawn
{
	GENERATED_BODY()

public:
	AMaxPayneCharacter();
	void Shoot();

	UFUNCTION(BlueprintPure)
	UMaxPayneAnimationHandler* GetAnimationHandler() const
	{
		return MaxPayneAnimationHandler;
	}

	virtual UPawnMovementComponent* GetMovementComponent() const override;

private:
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	                         AActor* DamageCauser) override;

	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;

	void SpawnPistol();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName OneHandWeaponAttachSocketName;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APistolWeapon> PistolWeaponClass;

	//Actors
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> CapsuleCollider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<APistolWeapon> PistolWeapon;

	//Actor Components

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UPlayerMovementComponent> PlayerMover;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UPlayerCombatHandler> CombatHandler;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMaxPayneCameraMover> MaxPayneCameraMover;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMaxPayneAnimationHandler> MaxPayneAnimationHandler;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPlayerHUD> PlayerHUD;

private:
	UPROPERTY(VisibleAnywhere)
	TArray<USkeletalMeshComponent*> AllSkeletalMeshComponents;
};
