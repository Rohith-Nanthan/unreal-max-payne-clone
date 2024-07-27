// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MaxPayneCameraMover.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AMaxPayneController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UMaxPayneCameraMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMaxPayneCameraMover();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Initialize(USpringArmComponent* SpringArmComponentToSet, UCameraComponent* CameraComponentToSet, AMaxPayneController* MaxPayneControllerToSet);

private:
	UPROPERTY()
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY()
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY()
	TObjectPtr<AMaxPayneController> MaxPayneController;
};
