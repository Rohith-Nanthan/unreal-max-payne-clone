// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/MaxPayneCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "PlayerMovementComponent.h"
#include "Camera/CameraComponent.h"

AMaxPayneCharacter::AMaxPayneCharacter()
{
	//Scene Components
	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->AttachToComponent(CapsuleCollider, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//Actor components
	PlayerMover = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("PlayerMover"));
	PlayerMover->UpdatedComponent = CapsuleCollider;

	PrimaryActorTick.bCanEverTick = false;
}
