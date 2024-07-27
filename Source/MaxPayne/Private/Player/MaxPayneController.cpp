// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MaxPayneController.h"

#include "MaxPayneCameraManager.h"
#include "MaxPayneCharacter.h"
#include "PlayerInputReaderComponent.h"
#include "PlayerMovementComponent.h"

AMaxPayneController::AMaxPayneController(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	PlayerInputReader = CreateDefaultSubobject<UPlayerInputReaderComponent>(TEXT("InputReader"));
	PlayerCameraManagerClass = AMaxPayneCameraManager::StaticClass();
}

void AMaxPayneController::SetupInputComponent()
{
	Super::SetupInputComponent();
	PlayerInputReader->SetupInputComponent(InputComponent, this);
}

void AMaxPayneController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	MaxPayneCharacter = Cast<AMaxPayneCharacter>(InPawn);
	if (MaxPayneCharacter == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Possessed pawn is not Max Payne Character"));
		return;
	}

	PlayerMover = Cast<UPlayerMovementComponent>(MaxPayneCharacter->GetMovementComponent());
	if (PlayerMover == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Movement component not found in MaxPayne Character"));
		return;
	}

	PlayerInputReader->OnJumpInputReceived.AddDynamic(this, &AMaxPayneController::OnJumpInputReceived);
	PlayerInputReader->OnMoveInputReceived.AddDynamic(this, &AMaxPayneController::OnMoveInputReceived);
	PlayerInputReader->OnLookInputReceived.AddDynamic(this, &AMaxPayneController::OnLookInputReceived);
	PlayerInputReader->OnShootInputReceived.AddDynamic(this, &AMaxPayneController::OnShootInputReceived);
}

void AMaxPayneController::OnUnPossess()
{
	Super::OnUnPossess();

	if (PlayerMover == nullptr)
	{
		return;
	}

	PlayerInputReader->OnJumpInputReceived.RemoveDynamic(this, &AMaxPayneController::OnJumpInputReceived);
	PlayerInputReader->OnMoveInputReceived.RemoveDynamic(this, &AMaxPayneController::OnMoveInputReceived);
	PlayerInputReader->OnLookInputReceived.RemoveDynamic(this, &AMaxPayneController::OnLookInputReceived);
	PlayerInputReader->OnShootInputReceived.RemoveDynamic(this, &AMaxPayneController::OnShootInputReceived);
}

void AMaxPayneController::OnJumpInputReceived()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Yellow,TEXT("Jump input received"));
	}

	if (PlayerMover == nullptr)
	{
		return;
	}

	PlayerMover->StartJumping();
}

void AMaxPayneController::OnMoveInputReceived(FVector2D MovementInput)
{
	if (PlayerMover == nullptr)
	{
		return;
	}

	const FVector ForwardMovement = GetForwardVectorProjectedAlong_XY_Plane() * MovementInput.X;
	const FVector StrafeMovement = GetRightVectorProjectedAlong_XY_Plane() * MovementInput.Y;
	const FVector MovementDirection = ForwardMovement + StrafeMovement;
	PlayerMover->MoveAlongDirection(MovementDirection);
}

void AMaxPayneController::OnLookInputReceived(FVector2D LookInput)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(3, 1.f, FColor::Yellow,TEXT("Look input received"));
	}

	AddPitchInput(LookInput.Y);
	AddYawInput(LookInput.X);
}

void AMaxPayneController::OnShootInputReceived()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Red,TEXT("Shoot input received"));
	}

	if (MaxPayneCharacter)
	{
		MaxPayneCharacter->Shoot();
	}
}
