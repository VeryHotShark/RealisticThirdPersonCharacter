// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cover.generated.h"

class USplineComponent;

UCLASS()
class REALISTICMOVEMENT_API ACover : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACover();

	UPROPERTY(BlueprintReadOnly)
	USplineComponent* SplineComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	FVector GetClosestCoverPoint(ACharacter* Character);

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure,BlueprintCallable)
	float GetClosestSplineDistanceAtLocation(FVector Location);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void EnterCover(ACharacter* Character);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void ExitCover(ACharacter* Character);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void UpdateCharacterPosition(ACharacter* Character, float MoveDirection);
};
