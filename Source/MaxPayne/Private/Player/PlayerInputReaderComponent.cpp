// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/PlayerInputReaderComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"

UPlayerInputReaderComponent::UPlayerInputReaderComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerInputReaderComponent::SetupInputComponent(UInputComponent* Inputcomponent,
                                                      APlayerController* PlayerController)
{
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(Inputcomponent);
	if (UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		EnhancedSubsystem->AddMappingContext(InputMappingContext, 0);
	}

	EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this,
	                                   &UPlayerInputReaderComponent::OnJumpTriggered);
	EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this,
	                                   &UPlayerInputReaderComponent::OnMoveTriggered);
}

void UPlayerInputReaderComponent::OnJumpTriggered()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, TEXT("Jump Pressed"));
	}

	OnJumpInputReceived.Broadcast();
}

void UPlayerInputReaderComponent::OnMoveTriggered(const FInputActionValue& InputActionValue)
{
	const FVector2D MoveInput = InputActionValue.Get<FVector2D>();
	if (GEngine)
	{
		const FString MoveInputValue = FString::Printf(TEXT("Move x: %f, y %f"), MoveInput.X, MoveInput.Y);
		GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Green, MoveInputValue);
	}

	OnMoveInputReceived.Broadcast(MoveInput);
}
