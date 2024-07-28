// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MaxPayneAnimationHandler.generated.h"

class AMaxPayneController;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UMaxPayneAnimationHandler : public UActorComponent
{
	GENERATED_BODY()

public:
	UMaxPayneAnimationHandler();

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void Initialize(USceneComponent* CharacterArtRoot, AMaxPayneController* MaxPayneController);

private:
	UPROPERTY()
	TObjectPtr<USceneComponent> ArtRoot;

	UPROPERTY()
	TObjectPtr<AMaxPayneController> Controller;
};
