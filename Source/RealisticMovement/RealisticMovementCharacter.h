// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "RealisticMovementCharacter.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	WALK,
	RUN,
	CROUCH,
	COVER,
	JUMP
};

UCLASS(config=Game)
class ARealisticMovementCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	ECharacterState CharacterState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	FVector2D MoveInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	FVector2D LookInput;

public:
	ARealisticMovementCharacter();
	

protected:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Character Actions")
	void StartJump();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Character Actions")
	void StopJump();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Character Actions")
	void StartCrouch();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Character Actions")
	void StopCrouch();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Character Actions")
	void StartCover();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Character Actions")
	void StopCover();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Character Actions")
	void StartRun();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Character Actions")
	void StopRun();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Character Actions")
	void HandleMoveInput(const FInputActionValue& Value);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Character Actions")
	void HandleLookInput(const FInputActionValue& Value);
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	
	FORCEINLINE FVector2D GetMoveInput() const { return MoveInput; }
	
	FORCEINLINE FVector2D GetLookInput() const { return LookInput; }
};

