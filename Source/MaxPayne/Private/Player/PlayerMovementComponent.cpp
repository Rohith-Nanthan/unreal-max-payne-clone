// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerMovementComponent.h"

// Sets default values for this component's properties
UPlayerMovementComponent::UPlayerMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
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
	else if (!IsOnGround())
	{
		Delta += GetFallDownDelta(DeltaTime);
	}

	Delta += GetWalkDelta(DeltaTime);

	const bool IsMovementSuccessful = SafeMoveUpdatedComponent(Delta, FQuat::Identity, true, LastMovementHitResult);
	Velocity = Delta;
	UpdateComponentVelocity();
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
	if (!bIsMoving)
	{
		return FVector::ZeroVector;
	}

	if (bIsReceivingMovementInput)
	{
		CurrentMovingSpeed += MoveDeAccleration * DeltaTime;
	}
	else
	{
		CurrentMovingSpeed -= MoveAccleration * DeltaTime;
	}

	CurrentMovingSpeed = FMath::Clamp(CurrentMovingSpeed, 0.f, MaxMoveSpeed);
	if (CurrentMovingSpeed == 0.f)
	{
		bIsMoving = false;
	}

	return MovementDirection * CurrentMovingSpeed * DeltaTime;
}

bool UPlayerMovementComponent::IsOnGround()
{
	FHitResult HitResult(1);
	FVector StartingLocation = GetActorFeetLocation();
	FVector EndLocation = StartingLocation + (FVector::DownVector * GroundDetectionDistance);
	DrawDebugLine(GetWorld(), StartingLocation, EndLocation, FColor::Red);
	return GetWorld()->SweepSingleByObjectType(HitResult, StartingLocation, EndLocation, FQuat::Identity,
	                                           FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
	                                           FCollisionShape::MakeCapsule(GroundDetectionCapsuleRadius,
	                                                                        GroundDetectionCapsuleHeight),
	                                           FCollisionQueryParams(FName(), false, GetOwner()));
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
	MovementDirection = Direction;
	bIsReceivingMovementInput = true;
	if (!bIsMoving)
	{
		CurrentMovingSpeed = StartingMoveSpeed;
		bIsMoving = true;
	}
}

void UPlayerMovementComponent::StopMoving()
{
	bIsReceivingMovementInput = false;
}
