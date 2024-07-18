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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Default)
	float GravitySpeed = 300.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Default)
	float RaycastDistanceForGround = 300.f;
	
	//Jump
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Jump)
	float JumpSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Jump)
	float JumpDuration = 2.f;

	//Walking
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Walk)
	float WalkingSpeed = 300.f;
	
private:
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

	void MoveAlongDirection(FVector Direction);
};
