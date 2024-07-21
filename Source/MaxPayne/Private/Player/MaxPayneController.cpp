// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MaxPayneController.h"

#include "MaxPayneCharacter.h"
#include "PlayerInputReaderComponent.h"
#include "PlayerMovementComponent.h"

AMaxPayneController::AMaxPayneController(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	PlayerInputReader = CreateDefaultSubobject<UPlayerInputReaderComponent>(TEXT("InputReader"));
}

void AMaxPayneController::SetupInputComponent()
{
	Super::SetupInputComponent();
	PlayerInputReader->SetupInputComponent(InputComponent, this);
}

void AMaxPayneController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (MaxPayneCharacter = Cast<AMaxPayneCharacter>(InPawn))
	{
		if (PlayerMover = Cast<UPlayerMovementComponent>(MaxPayneCharacter->GetMovementComponent()))
		{
			PlayerInputReader->OnJumpInputReceived.AddDynamic(this, &AMaxPayneController::OnJumpInputReceived);
			PlayerInputReader->OnMoveInputReceived.AddDynamic(this, &AMaxPayneController::OnMoveInputReceived);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Possessed pawn is not Max Payne Character"));
	}
}

void AMaxPayneController::OnUnPossess()
{
	Super::OnUnPossess();

	if (PlayerMover)
	{
		PlayerInputReader->OnJumpInputReceived.RemoveDynamic(this, &AMaxPayneController::OnJumpInputReceived);
		PlayerInputReader->OnMoveInputReceived.RemoveDynamic(this, &AMaxPayneController::OnMoveInputReceived);
	}
}

void AMaxPayneController::OnJumpInputReceived()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(3, 1.f, FColor::Yellow,TEXT("Jump input received"));
	}

	if (PlayerMover)
	{
		PlayerMover->StartJumping();
	}
}

void AMaxPayneController::OnMoveInputReceived(FVector2D MovementInput)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Yellow,TEXT("Move input received"));
	}

	if (PlayerMover)
	{
		const FVector MovementDirection(MovementInput.X, MovementInput.Y, 0.f);
		PlayerMover->MoveAlongDirection(MovementDirection);
	}
}
