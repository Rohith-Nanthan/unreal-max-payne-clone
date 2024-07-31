// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerHUD.h"
#include "Blueprint/UserWidget.h"

UPlayerHUD::UPlayerHUD()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerHUD::BeginPlay()
{
	Super::BeginPlay();
}


void UPlayerHUD::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerHUD::Initialize(APlayerController* PlayerControllerToSet)
{
	PlayerController = PlayerControllerToSet;
	HUD_Widget = CreateWidget<UUserWidget>(PlayerController, HUD_WidgetClass);
	if (HUD_Widget)
	{
		HUD_Widget->AddToViewport();
	}
}
