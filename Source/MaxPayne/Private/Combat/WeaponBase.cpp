// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/WeaponBase.h"

#include "WeaponShootComponent.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponShootComponent = CreateDefaultSubobject<UWeaponShootComponent>(TEXT("WeaponShooter"));
}

void AWeaponBase::Initialize(USceneComponent* HitTraceStartPointForShooting)
{
	WeaponShootComponent->Initialize(HitTraceStartPointForShooting);
}

void AWeaponBase::Shoot()
{
	if (WeaponShootComponent)
	{
		WeaponShootComponent->Shoot();
	}
}
