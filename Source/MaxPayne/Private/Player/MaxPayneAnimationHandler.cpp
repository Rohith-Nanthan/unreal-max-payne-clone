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
		const FVector BlendSpacePosition(MovementDirection.X * CurrentSpeed, MovementDirection.Y * CurrentSpeed, 0.f);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(8, 1.f, FColor::Red,
			                                 FString::Printf(TEXT("Speed:%s"), *BlendSpacePosition.ToString()));
		}

		for (USkeletalMeshComponent* Mesh : AllCharacterSkeletalMesh)
		{
			Mesh->GetSingleNodeInstance()->SetBlendSpacePosition(BlendSpacePosition);
		}
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

	for (USkeletalMeshComponent* Mesh : AllCharacterSkeletalMesh)
	{
		Mesh->PlayAnimation(MovementAnimationBlendSpace, true);
	}
}
