// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInputReaderComponent.generated.h"

class UInputMappingContext;
class UInputAction;
struct FEnhancedInputActionValueBinding;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class UPlayerInputReaderComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerInputReaderComponent();
	void SetupInputComponent(UInputComponent* Inputcomponent, APlayerController* PlayerController);

private:
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;

	FEnhancedInputActionValueBinding* MoveInputBinding;
	FEnhancedInputActionValueBinding* LookInputBinding;
	FEnhancedInputActionValueBinding* AimInputBinding;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> LookInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> JumpInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> MoveInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> AimInputAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> ShootInputAction;

public:
	FVector2d MoveInputVector;
	FVector2d LookInputVector;
	bool bIsAiming;

private:
	void OnJumpTriggered();
	void OnShootTriggered();

private:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInputStateChange);
	
public:
	FOnInputStateChange OnJumpInputReceived;	
	FOnInputStateChange OnShootInputReceived;
};
