// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCoverComponent.h"

#include "GameFramework/Character.h"

UCharacterCoverComponent::UCharacterCoverComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}

ACover* UCharacterCoverComponent::UpdateClosestCover_Implementation()
{
	ACover* PotentialCover = FindClosestCover();

	if(ClosestCover != PotentialCover)
	{
		ClosestCover = PotentialCover;
		
		if(PotentialCover != nullptr)
			OnClosestCoverFound.Broadcast(ClosestCover);
		else
			OnClosestCoverLost.Broadcast();
	}

	return PotentialCover;
}

void UCharacterCoverComponent::InitializeComponent()
{
	Super::InitializeComponent();
	Character = Cast<ACharacter>(GetOwner());
}

void UCharacterCoverComponent::SetCoverTransitionState_Implementation(bool State)
{
	bIsDuringTransition = State;
}

bool UCharacterCoverComponent::TryCover_Implementation()
{
	ACover* PotentialCover = FindClosestCover();

	if(PotentialCover == nullptr)
		return false;

	PotentialCover->EnterCover(Character, this);
	ActiveCover = PotentialCover;
	OnCoverEnter.Broadcast(ActiveCover);
	return true;
}

void UCharacterCoverComponent::UpdateCover_Implementation(float MoveDirection)
{
	if(ActiveCover != nullptr)
		ActiveCover->UpdateCharacterPosition(Character, this ,MoveDirection);
}

void UCharacterCoverComponent::ExitCover_Implementation()
{
	if(ActiveCover == nullptr)
		return;

	ActiveCover->ExitCover(Character, this);
	OnCoverExit.Broadcast();
	ActiveCover = nullptr;
}

