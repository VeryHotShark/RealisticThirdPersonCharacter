// Copyright Epic Games, Inc. All Rights Reserved.

#include "RealisticMovementCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


//////////////////////////////////////////////////////////////////////////
// ARealisticMovementCharacter

ARealisticMovementCharacter::ARealisticMovementCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many  more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; //  Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ARealisticMovementCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ARealisticMovementCharacter::StartJump_Implementation()
{
	Jump();
	SetCharacterState(ECharacterState::JUMP);
}

void ARealisticMovementCharacter::StopJump_Implementation()
{
	StopJumping();
	//SetCharacterState(ECharacterState::WALK);
}

void ARealisticMovementCharacter::StartCrouch_Implementation()
{
	Crouch();
	SetCharacterState(ECharacterState::CROUCH);
}

void ARealisticMovementCharacter::StopCrouch_Implementation()
{
	UnCrouch();
	SetCharacterState(ECharacterState::WALK);
}

void ARealisticMovementCharacter::StartCover_Implementation()
{
	SetCharacterState(ECharacterState::COVER);
}

void ARealisticMovementCharacter::StopCover_Implementation()
{
	SetCharacterState(ECharacterState::WALK);
}

void ARealisticMovementCharacter::StartRun_Implementation()
{
	SetCharacterState(ECharacterState::RUN);
}

void ARealisticMovementCharacter::StopRun_Implementation()
{
	SetCharacterState(ECharacterState::WALK);
}

void ARealisticMovementCharacter::HandleMoveInput_Implementation(const FInputActionValue& Value)
{
	Move(Value);
}

void ARealisticMovementCharacter::HandleLookInput_Implementation(const FInputActionValue& Value)
{
	Look(Value);
}

void ARealisticMovementCharacter::SetCharacterState_Implementation(ECharacterState NewState)
{
	if(CharacterState != NewState)
	{
		LastCharacterState = CharacterState;
		CharacterState = NewState;
		OnCharacterStateChanged(LastCharacterState, CharacterState);
	}
}

void ARealisticMovementCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ARealisticMovementCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}




