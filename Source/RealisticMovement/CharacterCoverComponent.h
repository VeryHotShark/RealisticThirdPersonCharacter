// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Coverable.h"
#include "Components/ActorComponent.h"
#include "CharacterCoverComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoverFound, ICoverable*, Cover);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCoverLost);

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class REALISTICMOVEMENT_API UCharacterCoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterCoverComponent();

protected:
	UPROPERTY(BlueprintReadOnly)
	ACharacter* Character;
	
	UPROPERTY(BlueprintReadWrite)
	TScriptInterface<ICoverable> ClosestCoverable;

	UPROPERTY(BlueprintReadWrite)
	TScriptInterface<ICoverable> ActiveCoverable; ;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	ICoverable* GetClosestCoverable();

public:
	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
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
	void UpdateCover(float Direction);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ExitCover();
	
	UFUNCTION(BlueprintCallable)
	bool IsDuringCover() { return  ActiveCoverable.GetInterface() != nullptr; }
	
	FORCEINLINE ICoverable* GetCurrentCoverable() const { return ClosestCoverable.GetInterface(); }
};
