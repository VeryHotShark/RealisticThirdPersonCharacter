// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cover.h"
#include "Components/ActorComponent.h"
#include "CharacterCoverComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoverFound, ACover*, Cover);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCoverLost);

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class REALISTICMOVEMENT_API UCharacterCoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterCoverComponent();

protected:
	UPROPERTY(BlueprintReadWrite)
	bool bIsDuringTransition;
	
	UPROPERTY(BlueprintReadOnly)
	ACharacter* Character;
	
	UPROPERTY(BlueprintReadWrite)
	ACover* ClosestCover;

	UPROPERTY(BlueprintReadWrite)
	ACover* ActiveCover; ;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	ACover* FindClosestCover();

	// Can be used in Tick for UI to Display Interact Message
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	ACover* UpdateClosestCover();
public:
	virtual void InitializeComponent() override;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCoverFound OnClosestCoverFound;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCoverLost OnClosestCoverLost;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCoverFound OnCoverEnter;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCoverLost OnCoverExit;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool TryCover();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateCover(float MoveDirection);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ExitCover();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetCoverTransitionState(bool State);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnCoverEndReached(float Direction);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsDuringCover() { return  ActiveCover != nullptr || IsDuringCoverTransition(); }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsDuringCoverTransition() { return  bIsDuringTransition; }
	
	FORCEINLINE ACover* GetCurrentCover() const { return ActiveCover; }
};
