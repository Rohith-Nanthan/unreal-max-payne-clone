// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int PreviousHealth;

public:
	bool ReduceHealth(int DamageAmount);

private:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChange, int, PreviousHealth, int, CurrentHealth);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

public:
	FOnHealthChange OnHealthChange;
	FOnDeath OnDeath;
};
