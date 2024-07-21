// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInputReaderComponent.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class UPlayerInputReaderComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerInputReaderComponent();
	void SetupInputComponent(UInputComponent* Inputcomponent, APlayerController* PlayerController);

private:
	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> LookInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> JumpInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> MoveInputAction;

private:
	void OnJumpTriggered();
	void OnMoveTriggered(const FInputActionValue& InputActionValue);
	void OnLookTriggered(const FInputActionValue& InputActionValue);

private:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumpInputReceived);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoveInputReceived, FVector2D, MovementInput);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLookInputReceived, FVector2D, LookInput);

public:
	FOnJumpInputReceived OnJumpInputReceived;
	FOnMoveInputReceived OnMoveInputReceived;
	FOnLookInputReceived OnLookInputReceived;
};
