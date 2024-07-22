// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/MaxPayneCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Combat/HealthComponent.h"
#include "PlayerMovementComponent.h"


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
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	PlayerMover = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("PlayerMover"));
	PlayerMover->UpdatedComponent = CapsuleCollider;

	PrimaryActorTick.bCanEverTick = false;
}

float AMaxPayneCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                     AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(9, 1.f, FColor::Red,  FString::Printf(TEXT("Took damage %f"), ActualDamage));
	}
	HealthComponent->ReduceHealth(ActualDamage);
	return ActualDamage;
}
