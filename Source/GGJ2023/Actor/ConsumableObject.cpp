// Fill out your copyright notice in the Description page of Project Settings.


#include "../Actor/ConsumableObject.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AConsumableObject::AConsumableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = sceneComponent;
	staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	staticMeshComponent->SetupAttachment(sceneComponent);
}

// Called when the game starts or when spawned
void AConsumableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AConsumableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

