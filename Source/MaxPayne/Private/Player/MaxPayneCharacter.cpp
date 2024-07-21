// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/MaxPayneCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"

#include "PlayerMovementComponent.h"
#include "Camera/CameraComponent.h"

AMaxPayneCharacter::AMaxPayneCharacter()
{
	//Scene Components
	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->AttachToComponent(CapsuleCollider, FAttachmentTransformRules::KeepRelativeTransform);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//Actor components
	PlayerMover = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("PlayerMover"));
	PlayerMover->UpdatedComponent = CapsuleCollider;

	PrimaryActorTick.bCanEverTick = false;
}

void AMaxPayneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("Setting player input component from character"));
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMaxPayneCharacter::BeginPlay()
{
	Super::BeginPlay();
	PrintController();
}

void AMaxPayneCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMaxPayneCharacter::PrintController()
{
	UE_LOG(LogTemp, Warning, TEXT("Controller is: %s"), *GetController()->GetClass()->GetName());
}
