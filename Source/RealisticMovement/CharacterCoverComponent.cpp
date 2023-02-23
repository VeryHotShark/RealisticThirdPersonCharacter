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

	ACover* PotentialCover = FindClosestCover();

	if(ClosestCover != PotentialCover)
	{
		ClosestCover = PotentialCover;
		
		if(PotentialCover != nullptr)
			OnClosestCoverFound.Broadcast(ClosestCover);
		else
			OnClosestCoverLost.Broadcast();
	} 
}

bool UCharacterCoverComponent::TryCover_Implementation()
{
	ACover* PotentialCover = FindClosestCover();

	if(PotentialCover == nullptr)
		return false;

	PotentialCover->EnterCover(Character);
	ActiveCover = PotentialCover;
	OnCoverEnter.Broadcast(ActiveCover);
	return true;
}

void UCharacterCoverComponent::UpdateCover_Implementation(FVector MoveInput)
{
	// if(ActiveCover != nullptr)
		// ActiveCover->UpdateCharacterPosition(Character,MoveInput.X);
}

void UCharacterCoverComponent::ExitCover_Implementation()
{
	if(ActiveCover == nullptr)
		return;

	ActiveCover->ExitCover(Character);
	OnCoverExit.Broadcast();
	ActiveCover = nullptr;
}

