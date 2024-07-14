// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "PlayerMovementComponent.generated.h"

UCLASS()
class UPlayerMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Jump)
	float JumpSpeed = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Jump)
	float JumpDuration = 2.f;

private:
	bool bIsJumping;
	float ElapsedJumpDuration;

private:
	void Jump(float DeltaTime);

public:
	void StartJumping();
	void StopJumping();
};
