// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MaxPayneController.h"

#include "MaxPayneCameraManager.h"
#include "MaxPayneCharacter.h"
#include "PlayerInputReaderComponent.h"
#include "PlayerMovementComponent.h"

AMaxPayneController::AMaxPayneController(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerInputReader = CreateDefaultSubobject<UPlayerInputReaderComponent>(TEXT("InputReader"));
	PlayerCameraManagerClass = AMaxPayneCameraManager::StaticClass();
}

void AMaxPayneController::Tick(float DeltaSeconds)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(6, 2.f, FColor::Yellow,TEXT("Controller updating"));
	}

	RotateControllerForLook();
	UpdateMovementDirection();
	
	Super::Tick(DeltaSeconds);
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
	PlayerInputReader->OnShootInputReceived.RemoveDynamic(this, &AMaxPayneController::OnShootInputReceived);
}

void AMaxPayneController::UpdateMovementDirection()
{
	const FVector2D MoveInput = PlayerInputReader->MoveInputVector;

	if (PlayerMover == nullptr)
	{
		return;
	}

	const bool bIsMoveInputReceived = !MoveInput.Equals(FVector2D::ZeroVector);
	if (bIsMoveInputReceived)
	{
		LastMovementDirection = MoveInput;
	}

	const FVector ForwardMovement = GetForwardVectorProjectedAlong_XY_Plane() * LastMovementDirection.Y;
	const FVector StrafeMovement = GetRightVectorProjectedAlong_XY_Plane() * LastMovementDirection.X;
	const FVector CameraBasedMovementDirection = (ForwardMovement + StrafeMovement).GetSafeNormal();
	PlayerMover->UpdateMovementData(CameraBasedMovementDirection, bIsMoveInputReceived);
}

void AMaxPayneController::RotateControllerForLook()
{
	const FVector2D LookInput = PlayerInputReader->LookInputVector;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(7, 2.f, FColor::Yellow,
		                                 FString::Printf(TEXT("Looking at %s."), *LookInput.ToString()));
	}

	LookRotator.Add(LookInput.Y, LookInput.X, 0.f);
	AddPitchInput(LookInput.Y);
	AddYawInput(LookInput.X);
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
