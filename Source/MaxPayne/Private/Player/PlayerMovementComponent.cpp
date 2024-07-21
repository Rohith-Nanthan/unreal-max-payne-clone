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

bool UPlayerMovementComponent::IsOnGround()
{
	FHitResult HitResult(1);
	FVector StartingLocation = GetActorFeetLocation();
	FVector EndLocation = StartingLocation + (FVector::DownVector * RaycastDistanceForGround);
	DrawDebugLine(GetWorld(), StartingLocation, EndLocation, FColor::Red);
	return GetWorld()->LineTraceSingleByObjectType(HitResult, StartingLocation, EndLocation,
	                                               FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
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
	AddInputVector(Direction.GetSafeNormal());
}
