// Fill out your copyright notice in the Description page of Project Settings.


#include "P38PlayerController.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AP38PlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* LocalPlayerSystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (LocalPlayerSystem && DefaultMappingContext)
	{
		LocalPlayerSystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AP38PlayerController::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
}
