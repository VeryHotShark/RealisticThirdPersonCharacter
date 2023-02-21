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
	
	PotentialCover->EnterCover(Character);
	ActiveCoverable = PotentialCover;
	OnCoverEnter.Broadcast(ActiveCoverable);
	return true;
}

void UCharacterCoverComponent::UpdateCover_Implementation(float Direction)
{
	if(ICoverable* ActiveCover = ActiveCoverable.GetInterface())
		ActiveCover->UpdateCharacterPosition(Character, Direction);
}

void UCharacterCoverComponent::ExitCover_Implementation()
{
	if(ActiveCoverable.GetInterface() == nullptr)
		return;

	ActiveCoverable.GetInterface()->ExitCover(Character);
	OnCoverExit.Broadcast();
	ActiveCoverable.SetInterface(nullptr);
}

