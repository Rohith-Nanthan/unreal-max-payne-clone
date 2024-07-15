// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "PlayerInputReaderComponent.h"
#include "PlayerMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	PlayerInputReader = CreateDefaultSubobject<UPlayerInputReaderComponent>(TEXT("InputReader"));

	PlayerMover = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("PlayerMover"));
	PlayerMover->UpdatedComponent = CapsuleCollider;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		PlayerInputReader->SetupInputComponent(PlayerInputComponent, PlayerController);
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerInputReader->OnJumpInputReceived.AddDynamic(this, &APlayerCharacter::OnJumpInputReceived);
	PlayerInputReader->OnMoveInputReceived.AddDynamic(this, &APlayerCharacter::OnMoveInputReceived);
}

void APlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	PlayerInputReader->OnJumpInputReceived.RemoveDynamic(this, &APlayerCharacter::OnJumpInputReceived);
	PlayerInputReader->OnMoveInputReceived.RemoveDynamic(this, &APlayerCharacter::OnMoveInputReceived);
}

void APlayerCharacter::OnJumpInputReceived()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(3, 1.f, FColor::Yellow,TEXT("Jump input received"));
	}

	PlayerMover->StartJumping();
}

void APlayerCharacter::OnMoveInputReceived(FVector2D MovementInput)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Yellow,TEXT("Move input received"));
	}

	const FVector MovementDirection(MovementInput.X, MovementInput.Y, 0.f);
	PlayerMover->MoveAlongDirection(MovementDirection);
}
