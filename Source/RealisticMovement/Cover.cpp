// Fill out your copyright notice in the Description page of Project Settings.


#include "Cover.h"

#include "Components/SplineComponent.h"

ACover::ACover()
{
}

// Called when the game starts or when spawned
void ACover::BeginPlay()
{
	Super::BeginPlay();
	SplineComponent = FindComponentByClass<USplineComponent>();
	
}

