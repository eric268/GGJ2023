// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC.generated.h"

/**
 * 
 */
UCLASS()
class GGJ2023_API APC : public APlayerController
{
	GENERATED_BODY()

public:
	APC();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
