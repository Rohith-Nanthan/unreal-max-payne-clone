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
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		PlayerInputReader->SetupInputComponent(PlayerInputComponent, PlayerController);
	}
}
