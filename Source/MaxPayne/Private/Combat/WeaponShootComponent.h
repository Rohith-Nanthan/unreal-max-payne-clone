// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponShootComponent.generated.h"

class UMaxPayneCameraMover;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UWeaponShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponShootComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	void Initialize(USceneComponent* HitTraceStartPointToSet, UMaxPayneCameraMover* CameraMoverComponent);
	void Shoot();

protected:
	UPROPERTY()
	TObjectPtr<USceneComponent> HitTraceStartPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HitTraceDistance = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int DamageAmount = 1;
};
