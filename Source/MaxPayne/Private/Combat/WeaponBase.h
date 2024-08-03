// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class UWeaponShootComponent;

UCLASS(Abstract)
class AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();

	void Initialize(USceneComponent* HitTraceStartPointForShooting);
	void Shoot();
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWeaponShootComponent> WeaponShootComponent;
	
};
