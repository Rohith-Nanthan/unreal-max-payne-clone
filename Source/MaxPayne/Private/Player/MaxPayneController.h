// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MaxPayneController.generated.h"

class UPlayerInputReaderComponent;
class UPlayerMovementComponent;
class APlayerCharacter;
/**
 * 
 */
UCLASS()
class AMaxPayneController : public APlayerController
{
	GENERATED_BODY()

public:
	AMaxPayneController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	AMaxPayneController();

protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UPlayerInputReaderComponent> PlayerInputReader;

private:
	UPROPERTY()
	TObjectPtr<APlayerCharacter> MaxPayneCharacter;

	UPROPERTY()
	TObjectPtr<UPlayerMovementComponent> PlayerMover;
	
private:
	UFUNCTION()
	void OnJumpInputReceived();

	UFUNCTION()
	void OnMoveInputReceived(FVector2D MovementInput);
};
