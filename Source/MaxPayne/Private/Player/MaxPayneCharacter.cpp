// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/MaxPayneCharacter.h"

#include "MaxPayneAnimationHandler.h"
#include "MaxPayneCameraMover.h"
#include "MaxPayneController.h"
#include "PlayerCombatHandler.h"
#include "PlayerHUD.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Combat/HealthComponent.h"
#include "PlayerMovementComponent.h"
#include "Combat/PistolWeapon.h"

AMaxPayneCharacter::AMaxPayneCharacter()
{
	//Scene Components
	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	SetRootComponent(CapsuleCollider);

	CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	CharacterMesh->AttachToComponent(CapsuleCollider, FAttachmentTransformRules::KeepRelativeTransform);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->AttachToComponent(CapsuleCollider, FAttachmentTransformRules::KeepRelativeTransform);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//Actor components
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	PlayerMover = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("PlayerMover"));
	PlayerMover->UpdatedComponent = CapsuleCollider;

	CombatHandler = CreateDefaultSubobject<UPlayerCombatHandler>(TEXT("CombatHandler"));
	MaxPayneAnimationHandler = CreateDefaultSubobject<UMaxPayneAnimationHandler>(TEXT("AnimationHandler"));
	MaxPayneCameraMover = CreateDefaultSubobject<UMaxPayneCameraMover>(TEXT("CameraMover"));
	PlayerHUD = CreateDefaultSubobject<UPlayerHUD>(TEXT("PlayerHUD"));

	PrimaryActorTick.bCanEverTick = false;
}

float AMaxPayneCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                     AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Red,
		                                 FString::Printf(TEXT("Took damage %f"), ActualDamage));
	}
	HealthComponent->ReduceHealth(ActualDamage);
	return ActualDamage;
}

void AMaxPayneCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AMaxPayneController* MaxPayneController = Cast<AMaxPayneController>(NewController);

	MaxPayneCameraMover->Initialize(SpringArmComponent, CameraComponent, MaxPayneController);
	MaxPayneAnimationHandler->Initialize(MaxPayneController, CapsuleCollider, CharacterMesh, PlayerMover);

	SpawnPistol();
	CombatHandler->Initialize(MaxPayneController->GetInputReader(), MaxPayneCameraMover, PistolWeapon);

	PlayerHUD->Initialize(MaxPayneController);
}

void AMaxPayneCharacter::Shoot()
{
	CombatHandler->Shoot();
}

void AMaxPayneCharacter::BeginPlay()
{
	Super::BeginPlay();
	SpawnPistol();
}

void AMaxPayneCharacter::SpawnPistol()
{
	if (PistolWeapon)
	{
		return;
	}

	FVector SpawnLocation = CharacterMesh->GetSocketLocation(OneHandWeaponAttachSocketName);

	PistolWeapon = GetWorld()->SpawnActor<APistolWeapon>(PistolWeaponClass);
	PistolWeapon->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform, OneHandWeaponAttachSocketName);
	PistolWeapon->Initialize(CameraComponent);
}
