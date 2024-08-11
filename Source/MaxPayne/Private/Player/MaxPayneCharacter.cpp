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
#include "Logging/StructuredLog.h"

AMaxPayneCharacter::AMaxPayneCharacter()
{
	//Scene Components
	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	SetRootComponent(CapsuleCollider);

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

void AMaxPayneCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UE_LOGFMT(LogTemp, Warning, "Post comp Initialized");
	GetComponents(USkeletalMeshComponent::StaticClass(), AllSkeletalMeshComponents);
	SpawnPistol();
}

void AMaxPayneCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	UE_LOGFMT(LogTemp, Warning, "Posess started");

	AMaxPayneController* MaxPayneController = Cast<AMaxPayneController>(NewController);

	MaxPayneCameraMover->Initialize(SpringArmComponent, CameraComponent, MaxPayneController);
	MaxPayneAnimationHandler->Initialize(MaxPayneController, CapsuleCollider, AllSkeletalMeshComponents, PlayerMover);

	CombatHandler->Initialize(MaxPayneController->GetInputReader(), MaxPayneCameraMover);

	PlayerHUD->Initialize(MaxPayneController);
}

void AMaxPayneCharacter::Shoot()
{
	CombatHandler->Shoot();
	MaxPayneAnimationHandler->PlayShootAnimation();
}

UPawnMovementComponent* AMaxPayneCharacter::GetMovementComponent() const
{
	return PlayerMover;
}

void AMaxPayneCharacter::BeginPlay()
{
	Super::BeginPlay();
	UE_LOGFMT(LogTemp, Warning, "Begin play");
}

void AMaxPayneCharacter::SpawnPistol()
{
	PistolWeapon = GetWorld()->SpawnActor<APistolWeapon>(PistolWeaponClass);

	if (AllSkeletalMeshComponents.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("No skeletal mesh found"));
		return;
	}

	USkeletalMeshComponent* MeshToAttachPistol = AllSkeletalMeshComponents[0];
	for (USkeletalMeshComponent* Mesh : AllSkeletalMeshComponents)
	{
		if (Mesh->DoesSocketExist(OneHandWeaponAttachSocketName))
		{
			MeshToAttachPistol = Mesh;
			break;
		}
	}


	bool bIsAttachmentSuccessful = PistolWeapon->AttachToComponent(MeshToAttachPistol,
	                                                               FAttachmentTransformRules::SnapToTargetNotIncludingScale,
	                                                               OneHandWeaponAttachSocketName);
	UE_LOGFMT(LogTemp, Warning, "Attach was: {0}", bIsAttachmentSuccessful);
	PistolWeapon->Initialize(CameraComponent);
	CombatHandler->SetWeapon(PistolWeapon);
}
