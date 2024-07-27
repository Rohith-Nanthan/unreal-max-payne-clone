// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/PlayerInputReaderComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"

UPlayerInputReaderComponent::UPlayerInputReaderComponent()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.f, FColor::Yellow,TEXT("Reader update enabled"));
	}
	PrimaryComponentTick.bCanEverTick = true;
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

	MoveInputBinding = &EnhancedInputComponent->BindActionValue(MoveInputAction);
	LookInputBinding = &EnhancedInputComponent->BindActionValue(LookInputAction);

	EnhancedInputComponent->BindAction(ShootInputAction, ETriggerEvent::Triggered, this,
	                                   &UPlayerInputReaderComponent::OnShootTriggered);
}

void UPlayerInputReaderComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	MoveInputVector = MoveInputBinding->GetValue().Get<FVector2D>();
	LookInputVector = LookInputBinding->GetValue().Get<FVector2d>();

	if (GEngine)
	{
		FString PrintStatement = FString::Printf(TEXT("Move %s; Look: %s"), *MoveInputVector.ToString(),
		                                         *LookInputVector.ToString());
		GEngine->AddOnScreenDebugMessage(68, 1.f, FColor::Red, PrintStatement);
	}

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
