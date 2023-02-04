// Fill out your copyright notice in the Description page of Project Settings.


#include "../Actor/CameraManager.h"
#include "../Misc/HelperFunctions.h"
#include "../Controllers/PC.h"
#include "../Pawns/PlayerCharacter.h"
ACameraManager::ACameraManager()
{

}
void ACameraManager::BeginPlay()
{
	Super::BeginPlay();
	auto pc = Cast<APC>(GetOwningPlayerController());
	if (pc)
	{
		auto player = Cast<APlayerCharacter>(pc->GetPawn());
		if (player)
		{
			ViewPitchMin = player->minPitch;
			ViewPitchMax = player->maxPitch;
			PRINT("SUCCESS");
		}
		else
			PRINT("FAILED");
	}
	else
		PRINT("FAILED");


}

void ACameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
