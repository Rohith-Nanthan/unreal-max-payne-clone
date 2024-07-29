// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MaxPayneController.generated.h"

class UPlayerInputReaderComponent;
class UPlayerMovementComponent;
class AMaxPayneCharacter;

UCLASS()
class AMaxPayneController : public APlayerController
{
	GENERATED_BODY()

public:
	explicit AMaxPayneController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	FORCEINLINE FVector GetForwardVectorProjectedAlong_XY_Plane() const
	{
		const FVector ControllerForwardDirection = LookRotator.Vector();
		return FVector::VectorPlaneProject(
			ControllerForwardDirection, FVector::UpVector);
	}

	FORCEINLINE FVector GetRightVectorProjectedAlong_XY_Plane() const
	{
		return GetForwardVectorProjectedAlong_XY_Plane().RotateAngleAxis(90, FVector::UpVector);
	}

private:
	UFUNCTION()
	void UpdateMovementDirection();

	UFUNCTION()
	void RotateControllerForLook();

	UFUNCTION()
	void OnJumpInputReceived();

	UFUNCTION()
	void OnShootInputReceived();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UPlayerInputReaderComponent> PlayerInputReader;

private:
	UPROPERTY()
	TObjectPtr<AMaxPayneCharacter> MaxPayneCharacter;

	UPROPERTY()
	TObjectPtr<UPlayerMovementComponent> PlayerMover;


public:
	UPROPERTY(VisibleAnywhere)
	FVector2D LastMovementDirection;

	UPROPERTY(VisibleAnywhere)
	FRotator LookRotator;

	UPlayerInputReaderComponent* GetInputReader() const
	{
		return  PlayerInputReader;
	}
};
