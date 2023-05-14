// The copyright of this project belongs to Kane.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Framework/UtilsEnums.h"
#include "MGAnimInstance.generated.h"


UCLASS()
class MYGAME_API UMGAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion")
	EMovementState MovementState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion")
	ELocomotionState PreLocomotionState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion")
	ELocomotionState LocomotionState;

	void OnUpdateLocomotionState(ELocomotionState NewState)
	{
		if (NewState != LocomotionState)
		{
			PreLocomotionState = LocomotionState;
			LocomotionState = NewState;
			if (LocomotionState == ELocomotionState::ELS_Idle)
				OnCastingAction();
		}
	}

	UFUNCTION()
	void OnCastingAction()
	{
		GetWorld()->GetTimerManager().ClearTimer(ResetTimerHandle);
		bInAttackState = true;
		GetWorld()->GetTimerManager().SetTimer(ResetTimerHandle, this, &UMGAnimInstance::ResetIdleAnim, ResetAttackTime, false);
	}

	UFUNCTION()
	void ResetIdleAnim()
	{
		bInAttackState = false;
	}

	/**
	 * @brief 用于切换attackIdle/normalIdle
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle")
	uint8 bInAttackState:1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle")
	float ResetAttackTime = 3.0f;
	FTimerHandle ResetTimerHandle;
};
