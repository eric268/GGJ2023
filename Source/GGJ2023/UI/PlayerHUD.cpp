// Fill out your copyright notice in the Description page of Project Settings.


#include "../UI/PlayerHUD.h"
#include "../Pawns/PlayerCharacter.h"
#include "../Misc/HelperFunctions.h"
#include "../UI/DialogueWidget.h"

APlayerHUD::APlayerHUD()
{
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
	playerCharacter = Cast<APlayerCharacter>(GetOwningPawn());
	if (!playerCharacter)
		PRINT("Could not find player character PlayerHUD.cpp");

	//static ConstructorHelpers::FClassFinder<UDialogueWidget> dialogue(TEXT("WidgetBlueprint'/Game/UI/Dialogue_W.Dialogue_W_C"));
	//if (dialogue.Succeeded())
	{
		//dialogueWidgetClass = dialogue.Class;

		//CreateWidget<dialogueWidgetClass>
	}
	//else
	{
		//PRINT("Failed to find dialogue widget class in PlayerHUD.cpp")
	}

}

