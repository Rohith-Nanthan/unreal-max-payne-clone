// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCharacter.generated.h"

class UCapsuleComponent;
class UPlayerInputReaderComponent;
class UPlayerMovementComponent;
UCLASS()
class APlayerCharacter : public APawn
{
	GENERATED_BODY()

public:
	APlayerCharacter();

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCapsuleComponent* CapsuleCollider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPlayerInputReaderComponent* PlayerInputReader;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UPlayerMovementComponent* PlayerMover;
};
