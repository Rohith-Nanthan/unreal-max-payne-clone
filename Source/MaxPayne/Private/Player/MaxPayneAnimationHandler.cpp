// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MaxPayneAnimationHandler.h"

#include "MaxPayneController.h"

UMaxPayneAnimationHandler::UMaxPayneAnimationHandler()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMaxPayneAnimationHandler::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (ArtRoot && Controller)
	{
		ArtRoot->SetWorldRotation(Controller->LookRotator);
	}
}

void UMaxPayneAnimationHandler::Initialize(USceneComponent* CharacterArtRoot, AMaxPayneController* MaxPayneController)
{
	ArtRoot = CharacterArtRoot;
	Controller = MaxPayneController;
}
