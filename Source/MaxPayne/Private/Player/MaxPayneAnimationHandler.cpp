// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MaxPayneAnimationHandler.h"

#include "MaxPayneController.h"
#include "PlayerMovementComponent.h"
#include "Animation/AnimSingleNodeInstance.h"

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
		ArtRoot->SetWorldRotation(FRotator(0.f, Controller->LookRotator.Yaw, 0.f));
	}
	if (Controller && MovementComponent)
	{
		const FVector2D MovementDirection = Controller->LastMovementDirection;
		const float CurrentSpeed = MovementComponent->GetCurrentMovementSpeed();
		LocomotionBlendParams = FVector(MovementDirection.X * CurrentSpeed, MovementDirection.Y * CurrentSpeed, 0.f);
	}
}

void UMaxPayneAnimationHandler::Initialize(AMaxPayneController* MaxPayneController, USceneComponent* CharacterArtRoot,
                                           TArray<USkeletalMeshComponent*>& AllSkeletalMesh,
                                           UPlayerMovementComponent* PlayerMovementComponent)
{
	ArtRoot = CharacterArtRoot;
	Controller = MaxPayneController;
	AllCharacterSkeletalMesh = AllSkeletalMesh;
	MovementComponent = PlayerMovementComponent;
}

void UMaxPayneAnimationHandler::PlayShootAnimation()
{
	for (USkeletalMeshComponent* Mesh : AllCharacterSkeletalMesh)
	{
		UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
		AnimInstance->Montage_Play(ShootAnimationMontage);
	}
}
