// Fill out your copyright notice in the Description page of Project Settings.


#include "P38Rocket.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AP38Rocket::AP38Rocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(20, 20, 20));
	Box->SetGenerateOverlapEvents(true);

	Rocket = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rocket"));
	Rocket->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Rocket(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_Rocket.SM_Rocket'"));
	if (SM_Rocket.Succeeded())
	{
		Rocket->SetStaticMesh(SM_Rocket.Object);
	}

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	Movement->ProjectileGravityScale = 0;
	Movement->InitialSpeed = 1000.0f;
	Movement->MaxSpeed = 2000.0f;
}

// Called when the game starts or when spawned
void AP38Rocket::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(3.0f);

	OnActorBeginOverlap.AddDynamic(this, &AP38Rocket::ProcessBeginOverlap);
}

// Called every frame
void AP38Rocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AP38Rocket::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	CallCPPToBPButCPP();
}

void AP38Rocket::CallCPPToBPButCPP_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("CPP Excute"));
}

