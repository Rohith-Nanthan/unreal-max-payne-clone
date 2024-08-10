// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MaxPayneAnimationHandler.generated.h"

class AMaxPayneController;
class UPlayerMovementComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UMaxPayneAnimationHandler : public UActorComponent
{
	GENERATED_BODY()

public:
	UMaxPayneAnimationHandler();

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void Initialize(AMaxPayneController* MaxPayneController, USceneComponent* CharacterArtRoot,
	                TArray<USkeletalMeshComponent*>& AllSkeletalMesh,
	                UPlayerMovementComponent* PlayerMovementComponent);

	void PlayShootAnimation();

	UFUNCTION(BlueprintPure)
	FVector GetLocomotionBlendParams() const
	{
		return LocomotionBlendParams;
	}

private:
	UPROPERTY()
	TObjectPtr<AMaxPayneController> Controller;

	UPROPERTY()
	TObjectPtr<USceneComponent> ArtRoot;

	UPROPERTY()
	TArray<USkeletalMeshComponent*> AllCharacterSkeletalMesh;

	UPROPERTY()
	TObjectPtr<UPlayerMovementComponent> MovementComponent;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> ShootAnimationMontage;

	FVector LocomotionBlendParams;
};
