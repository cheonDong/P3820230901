// Fill out your copyright notice in the Description page of Project Settings.


#include "P38Pawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "P38ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "P38Rocket.h"

// Sets default values
AP38Pawn::AP38Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(20, 20, 20));

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Body.SM_P38_Body'"));
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}

	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);
	Left->SetRelativeLocation(FVector(37.0f, -21.0f, 1.0f));

	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);
	Right->SetRelativeLocation(FVector(37.0f, 21.0f, 1.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Propeller.SM_P38_Propeller'"));
	if (SM_Body.Succeeded())
	{
		Left->SetStaticMesh(SM_Propeller.Object);
		Right->SetStaticMesh(SM_Propeller.Object);
	}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);
	Arrow->SetRelativeLocation(FVector(100, 0, 0));

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	ActorComponent = CreateDefaultSubobject<UP38ActorComponent>(TEXT("ActorComponent"));
}

// Called when the game starts or when spawned
void AP38Pawn::BeginPlay()
{
	Super::BeginPlay();
	
	ActorComponent->AddSceneComponent(Left);
	ActorComponent->AddSceneComponent(Right);
}

// Called every frame
void AP38Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector(), BoostValue);
}

// Called to bind functionality to input
void AP38Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(IA_Boost, ETriggerEvent::Triggered, this, &AP38Pawn::EnhancedBoost);
		EnhancedInputComponent->BindAction(IA_Boost, ETriggerEvent::Completed, this, &AP38Pawn::EnhancedUnBoost);
		EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AP38Pawn::EnhancedFire);
		EnhancedInputComponent->BindAction(IA_PitchAndRoll, ETriggerEvent::Triggered, this, &AP38Pawn::EnhancedPitchAndRoll);
	}
}

void AP38Pawn::EnhancedBoost(const FInputActionValue& Value)
{
	BoostValue = 1.0f;
}

void AP38Pawn::EnhancedUnBoost(const FInputActionValue& Value)
{
	BoostValue = 0.5f;
}

void AP38Pawn::EnhancedFire(const FInputActionValue& Value)
{
	if (RocketTemplate)
	{
		AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(RocketTemplate,
			Arrow->GetComponentLocation(),
			Arrow->GetComponentRotation());
	}
}

void AP38Pawn::EnhancedPitchAndRoll(const FInputActionValue& Value)
{
	FVector2D VectorValue = Value.Get<FVector2D>();

	if(!VectorValue.IsZero())
	{
		AddActorLocalRotation(FRotator(VectorValue.Y * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60.0f,
			0,
			VectorValue.X * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60.0f));
	}
}

