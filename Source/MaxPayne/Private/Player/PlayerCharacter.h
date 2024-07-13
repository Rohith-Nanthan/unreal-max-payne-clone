// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInputReader.h"
#include "GameFramework/Pawn.h"
#include "Components/ShapeComponent.h"
#include "PlayerCharacter.generated.h"

class UCapsuleComponent;


UCLASS()
class APlayerCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCapsuleComponent* CapsuleCollider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPlayerInputReader* PlayerInputReader;
};
