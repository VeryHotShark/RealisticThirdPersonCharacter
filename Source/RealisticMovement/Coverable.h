// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Coverable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI,Blueprintable)
class UCoverable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class REALISTICMOVEMENT_API ICoverable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	FVector GetClosestCoverPoint(ACharacter* Character);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void EnterCover(ACharacter* Character);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void ExitCover(ACharacter* Character);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void UpdateCharacterPosition(ACharacter* Character, FVector MoveDir);
};
