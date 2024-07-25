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
	EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this,
									   &UPlayerInputReaderComponent::OnLookTriggered);
	EnhancedInputComponent->BindAction(ShootInputAction, ETriggerEvent::Triggered, this,
									   &UPlayerInputReaderComponent::OnShootTriggered);
}

void UPlayerInputReaderComponent::OnJumpTriggered()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Red, TEXT("Jump Pressed"));
	}

	OnJumpInputReceived.Broadcast();
}

void UPlayerInputReaderComponent::OnShootTriggered()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Red, TEXT("Shoot Pressed"));
	}

	OnShootInputReceived.Broadcast();
}

void UPlayerInputReaderComponent::OnMoveTriggered(const FInputActionValue& InputActionValue)
{
	const FVector2D MoveInput = InputActionValue.Get<FVector2D>();
	if (GEngine)
	{
		const FString MoveInputValue = FString::Printf(TEXT("Move x: %f, y %f"), MoveInput.X, MoveInput.Y);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Green, MoveInputValue);
	}

	OnMoveInputReceived.Broadcast(MoveInput);
}

void UPlayerInputReaderComponent::OnLookTriggered(const FInputActionValue& InputActionValue)
{
	const FVector2D LookInput = InputActionValue.Get<FVector2D>();
	if (GEngine)
	{
		const FString MoveInputValue = FString::Printf(TEXT("Look x: %f, y %f"), LookInput.X, LookInput.Y);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Green, MoveInputValue);
	}

	OnLookInputReceived.Broadcast(LookInput);
}
