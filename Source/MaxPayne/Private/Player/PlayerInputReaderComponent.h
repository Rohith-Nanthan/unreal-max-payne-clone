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
	TObjectPtr<UInputAction> JumpInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> MoveInputAction;

private:
	void OnJumpTriggered();
	void OnMoveTriggered(const FInputActionValue& InputActionValue);

private:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumpInputReceived);

public:
	FOnJumpInputReceived OnJumpInputReceived;
};
