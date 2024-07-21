// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/PlayerCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"

#include "PlayerInputReaderComponent.h"
#include "PlayerMovementComponent.h"
#include "Camera/CameraComponent.h"

APlayerCharacter::APlayerCharacter()
{
	//Scene Components
	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->AttachToComponent(CapsuleCollider, FAttachmentTransformRules::KeepRelativeTransform);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//Actor components
	PlayerInputReader = CreateDefaultSubobject<UPlayerInputReaderComponent>(TEXT("InputReader"));
	PlayerMover = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("PlayerMover"));
	PlayerMover->UpdatedComponent = CapsuleCollider;

	PrimaryActorTick.bCanEverTick = false;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("Setting player input component from character"));
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

	PrintController();
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

void APlayerCharacter::PrintController()
{
	UE_LOG(LogTemp, Warning, TEXT("Controller is: %s"), *GetController()->GetClass()->GetName());
}
