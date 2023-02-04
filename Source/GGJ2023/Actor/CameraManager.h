// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "CameraManager.generated.h"

/**
 * 
 */
UCLASS()
class GGJ2023_API ACameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
public:
	ACameraManager();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
