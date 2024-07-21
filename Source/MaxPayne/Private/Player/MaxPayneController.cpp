// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MaxPayneController.h"

void AMaxPayneController::SetupInputComponent()
{
	UE_LOG(LogTemp, Warning, TEXT("Setting player input component from controller"));
	Super::SetupInputComponent();
}
