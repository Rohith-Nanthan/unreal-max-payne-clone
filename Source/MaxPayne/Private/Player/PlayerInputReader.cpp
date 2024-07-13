// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/PlayerInputReader.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"

UPlayerInputReader::UPlayerInputReader()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerInputReader::SetupInputComponent(UInputComponent* Inputcomponent, APlayerController* PlayerController)
{
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(Inputcomponent);
	if (UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		EnhancedSubsystem->AddMappingContext(InputMappingContext, 0);
	}

	EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this,
	                                   &UPlayerInputReader::OnJumpTriggered);
	EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this,
	                                   &UPlayerInputReader::OnMoveTriggered);
}

void UPlayerInputReader::OnJumpTriggered()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, TEXT("Jump Pressed"));
	}
}

void UPlayerInputReader::OnMoveTriggered(const FInputActionValue& InputActionValue)
{
	const FVector2d MoveInput = InputActionValue.Get<FVector2d>();
	if (GEngine)
	{
		const FString MoveInputValue = FString::Printf(TEXT("Move x: %f, y %f"), MoveInput.X, MoveInput.Y);
		GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Green, MoveInputValue);
	}
}
