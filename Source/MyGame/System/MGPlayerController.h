// The copyright of this project belongs to Kane.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Framework/UtilsEnums.h"
#include "GameFramework/PlayerController.h"
#include "MGPlayerController.generated.h"

class UMGAnimInstance;
class UCombatSystemComponent;
class AMGCharacter;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class MYGAME_API AMGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void HandleMove(const FInputActionValue& InputValue);
	UFUNCTION()
	void HandleLook(const FInputActionValue& InputValue);
	UFUNCTION()
	void DoJump();
	UFUNCTION()
	void DoDodge();

	UFUNCTION()
	void StartSprint();

	UFUNCTION()
	void StopSprint();

	UFUNCTION()
	void StartWalk();

	UFUNCTION()
	void StopWalk();

	UFUNCTION()
	void DoLightAttack();
	UFUNCTION()
	void DoHeavyAttack();
	UFUNCTION()
	void DoChargeAttack();
	UFUNCTION()
	void DoSkillAttack();

protected:
	UPROPERTY()
	AMGCharacter* PlayerChar;
	UPROPERTY()
	UCombatSystemComponent* CombatSystemComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput", meta=(AllowPrivateAccess="true"))
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput|Action|Locomotion", meta=(AllowPrivateAccess="true"))
	UInputAction* IA_Move;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput|Action|Locomotion", meta=(AllowPrivateAccess="true"))
	UInputAction* IA_Look;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput|Action|Locomotion", meta=(AllowPrivateAccess="true"))
	UInputAction* IA_Jump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput|Action|Locomotion", meta=(AllowPrivateAccess="true"))
	UInputAction* IA_Dodge;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput|Action|Locomotion", meta=(AllowPrivateAccess="true"))
	UInputAction* IA_Sprint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput|Action|Locomotion", meta=(AllowPrivateAccess="true"))
	UInputAction* IA_Walk;

	UMGAnimInstance* AnimInstance;
	ELocomotionState DesireLocomotionState;
	FVector currentInputValue;
	uint8 bPressedSprint:1;
	uint8 bPressedWalk:1;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput|Action|Locomotion", meta=(AllowPrivateAccess="true"))
	UInputAction* IA_Displacement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput|Action|Attack", meta=(AllowPrivateAccess="true"))
	UInputAction* IA_DisplacementAttack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput|Action|Attack", meta=(AllowPrivateAccess="true"))
	UInputAction* IA_LightAttack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput|Action|Attack", meta=(AllowPrivateAccess="true"))
	UInputAction* IA_HeavyAttack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput|Action|Attack", meta=(AllowPrivateAccess="true"))
	UInputAction* IA_ChargeAttack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput|Action|Attack", meta=(AllowPrivateAccess="true"))
	UInputAction* IA_SkillAttack;
};
