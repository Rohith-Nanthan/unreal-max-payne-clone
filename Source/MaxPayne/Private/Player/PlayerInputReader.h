// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInputReader.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class UPlayerInputReader : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerInputReader();
	void SetupInputComponent(UInputComponent* Inputcomponent, APlayerController* PlayerController);

private:
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* JumpInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* MoveInputAction;

private:
	void OnJumpTriggered();
	void OnMoveTriggered(const FInputActionValue& InputActionValue);
};
