// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyCharacter.h"

#include "Combat/HealthComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	PrimaryActorTick.bCanEverTick = false;
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(215, 1.f, FColor::Red,  FString::Printf(TEXT("Enemy Took damage %f"), ActualDamage));
	}
	HealthComponent->ReduceHealth(ActualDamage);
	return ActualDamage;
}
