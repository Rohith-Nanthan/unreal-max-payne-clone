// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "PlayerInputReader.h"

#include "Player/PlayerCharacter.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	PlayerInputReader = CreateDefaultSubobject<UPlayerInputReader>(TEXT("InputReader"));
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		PlayerInputReader->SetupInputComponent(PlayerInputComponent, PlayerController);
	}
}