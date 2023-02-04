// Fill out your copyright notice in the Description page of Project Settings.


#include "../Controllers/PC.h"
#include "../Actor/CameraManager.h"

APC::APC()
{
	PlayerCameraManagerClass = ACameraManager::StaticClass();
}

void APC::BeginPlay()
{
	Super::BeginPlay();
}

void APC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}