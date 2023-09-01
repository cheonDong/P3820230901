// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P38ActorComponent.generated.h"

class USceneComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P3820230831_API UP38ActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UP38ActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<USceneComponent*> Propellers;

	UFUNCTION(BlueprintCallable, Category = "Data")
	void AddSceneComponent(USceneComponent* uSceneComponent);
};
