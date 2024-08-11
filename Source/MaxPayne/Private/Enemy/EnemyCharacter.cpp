// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyCharacter.h"

#include "Combat/HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(CapsuleComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	CharacterMovementComponent = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("Character Mover"));
	if (CharacterMovementComponent)
	{
		CharacterMovementComponent->UpdatedComponent = CapsuleComponent;
	}
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                  AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(215, 1.f, FColor::Red,
		                                 FString::Printf(TEXT("Enemy Took damage %f"), ActualDamage));
	}
	HealthComponent->ReduceHealth(ActualDamage);
	return ActualDamage;
}
