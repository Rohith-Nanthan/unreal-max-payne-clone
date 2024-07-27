// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MaxPayneCameraMover.h"

#include "MaxPayneController.h"
#include "GameFramework/SpringArmComponent.h"

UMaxPayneCameraMover::UMaxPayneCameraMover()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMaxPayneCameraMover::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (MaxPayneController && SpringArmComponent)
	{
		SpringArmComponent->SetWorldRotation(MaxPayneController->LookRotator);
	}
}

void UMaxPayneCameraMover::Initialize(USpringArmComponent* SpringArmComponentToSet,
                                      UCameraComponent* CameraComponentToSet,
                                      AMaxPayneController* MaxPayneControllerToSet)
{
	SpringArmComponent = SpringArmComponentToSet;
	CameraComponent = CameraComponentToSet;
	MaxPayneController = MaxPayneControllerToSet;
	if (!MaxPayneController)
	{
		UE_LOG(LogTemp, Error, TEXT("Controller is not AMaxPayneController"));
	}
}
