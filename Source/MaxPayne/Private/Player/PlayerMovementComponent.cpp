// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerMovementComponent.h"

// Sets default values for this component's properties
UPlayerMovementComponent::UPlayerMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsJumping)
	{
		Jump(DeltaTime);
	}
}

void UPlayerMovementComponent::Jump(float DeltaTime)
{
	if (ElapsedJumpDuration >= JumpDuration)
	{
		StopJumping();
		return;
	}

	const FVector JumpVector = FVector::UpVector * JumpSpeed * DeltaTime;
	MoveUpdatedComponent(JumpVector, FQuat::Identity, true);
	ElapsedJumpDuration += DeltaTime;
}

void UPlayerMovementComponent::StartJumping()
{
	if (bIsJumping)
	{
		return;
	}

	bIsJumping = true;
	ElapsedJumpDuration = 0.f;
}

void UPlayerMovementComponent::StopJumping()
{
	bIsJumping = false;
	ElapsedJumpDuration = 0.f;
}
