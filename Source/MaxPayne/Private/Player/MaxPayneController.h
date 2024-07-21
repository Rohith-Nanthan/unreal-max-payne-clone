// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MaxPayneController.generated.h"

/**
 * 
 */
UCLASS()
class AMaxPayneController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;
};
