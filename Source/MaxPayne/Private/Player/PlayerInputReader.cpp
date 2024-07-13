// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/PlayerInputReader.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"

// Sets default values for this component's properties
UPlayerInputReader::UPlayerInputReader()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPlayerInputReader::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UPlayerInputReader::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
	UE_LOG(LogTemp, Warning, TEXT("On jump input pressed"));
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
