// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MaxPayneCharacter.generated.h"

class UCapsuleComponent;
class UPlayerMovementComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class AMaxPayneCharacter : public APawn
{
	GENERATED_BODY()

public:
	AMaxPayneCharacter();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> CapsuleCollider;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UPlayerMovementComponent> PlayerMover;
};
