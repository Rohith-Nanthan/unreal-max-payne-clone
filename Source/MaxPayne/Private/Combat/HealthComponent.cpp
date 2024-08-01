// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PreviousHealth = CurrentHealth = StartingHealth;
	PrimaryComponentTick.bCanEverTick = true;
}

bool UHealthComponent::ReduceHealth(int DamageAmount)
{
	if (CurrentHealth == 0)
	{
		return false;
	}

	PreviousHealth = CurrentHealth;
	CurrentHealth -= DamageAmount;

	if (CurrentHealth < 0)
	{
		CurrentHealth = 0;
	}

	OnHealthChange.Broadcast(PreviousHealth, CurrentHealth);
	
	if (CurrentHealth == 0)
	{
		OnDeath.Broadcast();
	}
	
	return true;
}
