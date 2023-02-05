// Fill out your copyright notice in the Description page of Project Settings.


#include "../UI/PlayerHUD.h"
#include "../Pawns/PlayerCharacter.h"
#include "../Misc/HelperFunctions.h"
#include "../UI/DialogueWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"

APlayerHUD::APlayerHUD()
{
	static ConstructorHelpers::FClassFinder<UDialogueWidget> dialogue(TEXT("WidgetBlueprint'/Game/UI/Dialogue_W.Dialogue_W_C'"));
	if (dialogue.Succeeded())
	{
		dialogueWidgetClass = dialogue.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> bar(TEXT("WidgetBlueprint'/Game/UI/SizeBar_W.SizeBar_W_C'"));
	if (bar.Succeeded())
	{
		sizeBarClass = bar.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> gameOver(TEXT("WidgetBlueprint'/Game/UI/SizeBar_W.SizeBar_W_C'"));
	if (gameOver.Succeeded())
	{
		gameOverClass = gameOver.Class;
	}
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
	playerCharacter = Cast<APlayerCharacter>(GetOwningPawn());
	if (!playerCharacter)
		PRINT("Could not find player character PlayerHUD.cpp");
	
	UDialogueWidget* dWidget = GetDialogueWidget();
	if (dWidget)
	{
		dWidget->AddToViewport(0);
	}
	if (sizeBarClass)
	{
		sizeBarWidget = CreateWidget<UUserWidget>(GetWorld(), sizeBarClass);
		if (sizeBarWidget)
		{
			sizeBarWidget->AddToViewport(0);
		}
		else
		{
			PRINT("Error creating size bar widget");
		}
	}
	else
	{
		PRINT("Size bar widget class not found");
	}
}

UDialogueWidget* APlayerHUD::GetDialogueWidget()
{
	if (dialogueWidget)
	{
		return dialogueWidget;
	}
	else
	{
		if (dialogueWidgetClass)
		{
			dialogueWidget = CreateWidget<UDialogueWidget>(GetWorld(), dialogueWidgetClass);
			if (dialogueWidget)
			{
				return dialogueWidget;
			}
			else
			{
				PRINT("Error creating dialogue widget");
				return nullptr;
			}
		}
		else
		{
			PRINT("Dialogue widget class not found");
			return nullptr;
		}
	}
}

void APlayerHUD::OnGameOver()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	if (gameOverClass)
	{
		gameOverWidget = CreateWidget<UUserWidget>(GetWorld(), gameOverClass);
		if (gameOverWidget)
		{
			gameOverWidget->AddToViewport(0);
		}
		else
		{
			PRINT("Error creating game over widget");
		}
	}
	else
	{
		PRINT("Game over widget class not found");
	}
}