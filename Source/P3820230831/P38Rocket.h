// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "P38Rocket.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class P3820230831_API AP38Rocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AP38Rocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "component")
	UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "component")
	UStaticMeshComponent* Rocket;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "component")
	UProjectileMovementComponent* Movement;

	UFUNCTION()
	void ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintNativeEvent)
	void CallCPPToBPButCPP();
	void CallCPPToBPButCPP_Implementation();
};
