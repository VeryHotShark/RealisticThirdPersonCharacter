// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCoverComponent.h"

#include "GameFramework/Character.h"

UCharacterCoverComponent::UCharacterCoverComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}

void UCharacterCoverComponent::InitializeComponent()
{
	Super::InitializeComponent();
	Character = Cast<ACharacter>(GetOwner());
}

void UCharacterCoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TScriptInterface<ICoverable> PotentialCover = FindClosestCoverable();

	if(ClosestCoverable != PotentialCover)
	{
		ClosestCoverable = PotentialCover;
		
		if(PotentialCover != nullptr)
			OnClosestCoverFound.Broadcast(ClosestCoverable);
		else
			OnClosestCoverLost.Broadcast();
	} 
}

bool UCharacterCoverComponent::TryCover_Implementation()
{
	TScriptInterface<ICoverable> PotentialCover = FindClosestCoverable();

	if(PotentialCover == nullptr)
		return false;

	ICoverable::Execute_EnterCover(PotentialCover.GetObject(), Character);
	ActiveCoverable = PotentialCover;
	OnCoverEnter.Broadcast(ActiveCoverable);
	return true;
}

void UCharacterCoverComponent::UpdateCover_Implementation(float Direction)
{
	if(ActiveCoverable != nullptr)
		ICoverable::Execute_UpdateCharacterPosition(ActiveCoverable.GetObject(), Character, Direction);
}

void UCharacterCoverComponent::ExitCover_Implementation()
{
	if(ActiveCoverable == nullptr)
		return;

	ICoverable::Execute_ExitCover(ActiveCoverable.GetObject(), Character);
	OnCoverExit.Broadcast();
	ActiveCoverable = nullptr;
}

