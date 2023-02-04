// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConsumableObject.generated.h"

class UStaticMeshComponent;
class USceneComponent;

UCLASS()
class GGJ2023_API AConsumableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConsumableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		float currentSize = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		float sizeChangeOnConsumed = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		float launchFactor = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		float sizeDecreaseRatio = 0.1f;

};
