// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/WeaponShootComponent.h"

#include "Enemy/EnemyCharacter.h"
#include "Engine/DamageEvents.h"

UWeaponShootComponent::UWeaponShootComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponShootComponent::Initialize(USceneComponent* HitTraceStartPointToSet)
{
	HitTraceStartPoint = HitTraceStartPointToSet;
}

void UWeaponShootComponent::Shoot()
{
	if (HitTraceStartPoint == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Hit trace start point not assigned"));
		return;
	}

	FHitResult HitResult(1.f);

	FVector StartLocation(HitTraceStartPoint->GetComponentLocation());
	FVector TraceLine = HitTraceStartPoint->GetForwardVector() * HitTraceDistance;
	FVector EndLocation = StartLocation + TraceLine;

	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 1.f);
	bool IsHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation,
	                                                  ECollisionChannel::ECC_Pawn);

	if (IsHit)
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.f, 16, FColor::Red, false, 2.f);
		AActor* HitActor = HitResult.GetActor();
		AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(HitActor);

		if (EnemyCharacter)
		{
			EnemyCharacter->TakeDamage(DamageAmount, FPointDamageEvent(), GetOwner()->GetInstigatorController(),
			                           GetOwner());
		}
	}
}
