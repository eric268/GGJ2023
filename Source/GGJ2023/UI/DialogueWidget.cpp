// Fill out your copyright notice in the Description page of Project Settings.


#include "../UI/DialogueWidget.h"
#include "../Misc/HelperFunctions.h"
#include "../Pawns/PlayerCharacter.h"

void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (!playerCharacter)
	{
		playerCharacter = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	}
	else
	{
		PRINT("Player character not found in DialogueWidget.ccp");
	}
}
void UDialogueWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
}

void UDialogueWidget::AddDialogueText(FString text)
{
	mDialogueContainer.Enqueue(text);
}

void UDialogueWidget::StartDialogueSystem()
{
	if (!playerCharacter || isRunning)
		return;
	else
		DisplayDialogue();
}

void UDialogueWidget::DisplayDialogue()
{
	isRunning = true;
	if (mDialogueContainer.IsEmpty())
	{
		GetWorld()->GetTimerManager().ClearTimer(mIntroHandle);
		return;
	}
	FString word = *mDialogueContainer.Peek();
	AnimateText(word);
	mDialogueContainer.Pop();
}

void UDialogueWidget::ClearText()
{
	mDialogueText = "";
	mNewText = "";
}

void UDialogueWidget::AnimateText(FString newText)
{
	mNewText = newText;
	mLetterCounter = 0;
	mTextOpacity = 1.0f;
	UpdateTextOpacity();
	mDialogueText = "";
	GetWorld()->GetTimerManager().SetTimer(mTimerHandle, this, &UDialogueWidget::FadeInText, mFadeSpeed, true);
}

void UDialogueWidget::FadeInText()
{
	if (mNewText.Len() <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(mTimerHandle);
		return;
	}
	mDialogueText.AppendChar(mNewText[mLetterCounter]);
	mLetterCounter++;
	if (mLetterCounter >= mNewText.Len())
	{
		GetWorld()->GetTimerManager().ClearTimer(mTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(mFadeOutHandle, this, &UDialogueWidget::BeingTextFadeout, mTextDisplayTimer, false);
	}
}

void UDialogueWidget::FadeOutText()
{
	if (!playerCharacter)
		return;
	mTextOpacity -= GetWorld()->DeltaTimeSeconds;
	UpdateTextOpacity();
	if (mTextOpacity <= 0.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(mFadeOutHandle);
		if (!mDialogueContainer.IsEmpty())
		{
			GetWorld()->GetTimerManager().SetTimer(mIntroHandle, this, &UDialogueWidget::DisplayDialogue, 0.25f, false);
		}
		else
		{
			isRunning = false;
		}
	}
}

void UDialogueWidget::BeingTextFadeout()
{
	GetWorld()->GetTimerManager().SetTimer(mFadeOutHandle, this, &UDialogueWidget::FadeOutText, GetWorld()->DeltaTimeSeconds, true);
}