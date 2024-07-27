// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "PlayerMovementComponent.generated.h"

UCLASS()
class UPlayerMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	UPlayerMovementComponent();

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Default)
	float GravitySpeed = 300.f;

	//Ground detection

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=GroundDetection)
	float GroundDetectionDistance = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=GroundDetection)
	float GroundDetectionCapsuleRadius = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=GroundDetection)
	float GroundDetectionCapsuleHeight = 30.f;

	//Jump

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Jump)
	float JumpSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Jump)
	float JumpDuration = 2.f;

	//Walking

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Movement)
	float StartingMoveSpeed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Movement)
	float MaxMoveSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Movement)
	float MoveAccleration = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Movement)
	float MoveDeAccleration = 200.f;

private:
	bool bIsReceivingMovementInput;
	bool bIsMoving;
	FVector MovementDirection;
	float CurrentMovingSpeed = 0.f;

	bool bIsJumping;
	float ElapsedJumpDuration;
	FHitResult LastMovementHitResult;

private:
	FVector GetJumpDelta(float DeltaTime);
	FVector GetFallDownDelta(float DeltaTime);
	FVector GetWalkDelta(float DeltaTime);

	bool IsOnGround();

public:
	void StartJumping();
	void StopJumping();

	void UpdateMovementData(FVector NewMovementDirection, bool bIsMoveInputreceived);
};
