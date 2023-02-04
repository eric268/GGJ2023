// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
class APlayerCharacter;
class UDialogueWidget;

UCLASS()
class GGJ2023_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
public:
	APlayerHUD();
	virtual void BeginPlay() override;
	
	TSubclassOf<UUserWidget> sizeBarClass;
	UUserWidget* sizeBarWidget;

	TSubclassOf<UUserWidget> dialogueWidgetClass;
	UDialogueWidget* dialogueWidget;
	APlayerCharacter* playerCharacter;

	UDialogueWidget* GetDialogueWidget();

};
