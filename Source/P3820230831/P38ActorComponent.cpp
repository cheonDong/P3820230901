// Fill out your copyright notice in the Description page of Project Settings.


#include "P38ActorComponent.h"

// Sets default values for this component's properties
UP38ActorComponent::UP38ActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UP38ActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UP38ActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (auto Propeller : Propellers)
	{
		Propeller->AddLocalRotation(FRotator(0, 0, 3200.0 * DeltaTime));
	}
}

void UP38ActorComponent::AddSceneComponent(USceneComponent* uSceneComponent)
{
	if (uSceneComponent)
	{
		Propellers.Add(uSceneComponent);
	}
}

