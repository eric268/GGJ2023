// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define PRINT(x) GEngine->AddOnScreenDebugMessage(1, 2, FColor::Red, FString::Printf(TEXT(x)));
#define DEBUGMESSAGE(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(1, 2, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}
#define PRINTLOG(x) UE_LOG(LogTemp, Warning, TEXT(x));
#define LOGMESSAGE(x, ...) UE_LOG(LogTemp, Warning, FString::Printf(TEXT(x), __VA__ARGS__));

#include "CoreMinimal.h"

/**
 * 
 */
class GGJ2023_API HelperFunctions
{
public:
	HelperFunctions();
	~HelperFunctions();
};
