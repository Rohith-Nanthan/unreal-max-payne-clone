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

	FVector Delta = FVector::ZeroVector;
	if (bIsJumping)
	{
		Delta += GetJumpDelta(DeltaTime);
	}
	else
	{
		Delta += GetFallDownDelta(DeltaTime);
	}

	Delta += GetWalkDelta(DeltaTime);

	SafeMoveUpdatedComponent(Delta, FQuat::Identity, true, LastMovementHitResult);
}

FVector UPlayerMovementComponent::GetJumpDelta(float DeltaTime)
{
	if (ElapsedJumpDuration >= JumpDuration)
	{
		StopJumping();
		return FVector::ZeroVector;
	}

	ElapsedJumpDuration += DeltaTime;
	return FVector::UpVector * JumpSpeed * DeltaTime;
}

FVector UPlayerMovementComponent::GetFallDownDelta(float DeltaTime)
{
	return FVector::DownVector * GravitySpeed * DeltaTime;
}

FVector UPlayerMovementComponent::GetWalkDelta(float DeltaTime)
{
	return ConsumeInputVector() * WalkingSpeed * DeltaTime;
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

void UPlayerMovementComponent::MoveAlongDirection(FVector Direction)
{
	AddInputVector(Direction.GetSafeNormal());
}
