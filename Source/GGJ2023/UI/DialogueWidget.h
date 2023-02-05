// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Containers/Queue.h"
#include "DialogueWidget.generated.h"

/**
 * 
 */
class APlayerCharacter;
UCLASS()
class GGJ2023_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	APlayerCharacter* playerCharacter;
	
	bool mFadeOut = false;
	bool mFadeInText = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FString mDialogueText;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float mTextOpacity;
	TQueue<FString> mDialogueContainer;
	FString mNewText;
	FTimerHandle mTimerHandle;
	FTimerHandle mFadeOutHandle;
	FTimerHandle mIntroHandle;
	FTimerHandle mUnpauseHandle;
	float mFadeSpeed = 0.025f;
	float mTextDisplayTimer = 2.0f;

	bool isRunning = false;
	int mLetterCounter = 0;

	void AddDialogueText(FString text);
	void StartDialogueSystem();
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateTextOpacity();
	
private:
	void DisplayDialogue();
	void ClearText();
	void AnimateText(FString newText = "");
	void FadeInText();
	void FadeOutText();
	void BeingTextFadeout();
	void UnPauseSim();
};
