// The copyright of this project belongs to Kane.


#include "System/MGPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/MGAnimInstance.h"
#include "Character/MGCharacter.h"
#include "Combat/CombatSystemComponent.h"
#include "Helper/DebugHelper.h"
#include "Kismet/KismetMathLibrary.h"

void AMGPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMGPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	if (currentInputValue.Size() == 0.0f)
	{
		DesireLocomotionState = ELocomotionState::ELS_Idle;
	}
	else
	{
		if (bPressedSprint)
		{
			DesireLocomotionState = ELocomotionState::ELS_Sprint;
		}
		else if (bPressedWalk)
		{
			DesireLocomotionState = ELocomotionState::ELS_Walk;
		}
		else
		{
			// 比对大小
			if (currentInputValue.Size() > 0.45f && currentInputValue.Size() <= 0.65f)
			{
				DesireLocomotionState = ELocomotionState::ELS_Walk;
			}
			else if (currentInputValue.Size() > 0.65f)
			{
				DesireLocomotionState = ELocomotionState::ELS_Jog;
			}
			else
			{
				DesireLocomotionState = ELocomotionState::ELS_Idle;
			}
		}
		if (DesireLocomotionState != ELocomotionState::ELS_Idle)
		{
			FRotator conRot = GetControlRotation();
			conRot.Pitch = 0.0f;
			conRot.Roll = 0.0f;

			FVector ForwardVector = UKismetMathLibrary::GetForwardVector(conRot);
			FVector RightVector = UKismetMathLibrary::GetRightVector(conRot);
			// 处理转向
			FVector direction = ForwardVector * currentInputValue.Y + RightVector * currentInputValue.X;
			FRotator dirRot = direction.Rotation();
			PlayerChar->SetActorRotation(dirRot);
		}
	}
	if (AnimInstance)
		AnimInstance->OnUpdateLocomotionState(DesireLocomotionState);
	currentInputValue = FVector(0.0f);
}

void AMGPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PlayerChar = Cast<AMGCharacter>(InPawn);

	if (PlayerChar)
	{
		CombatSystemComp = PlayerChar->CombatSystemComp;
		AnimInstance = Cast<UMGAnimInstance>(PlayerChar->GetMesh()->GetAnimInstance());
	}
}

void AMGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();


	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		if (IA_Move)
		{
			EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this,
			                                   &AMGPlayerController::HandleMove);
		}

		if (IA_Look)
		{
			EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this,
			                                   &AMGPlayerController::HandleLook);
		}
		if (IA_Jump)
		{
			EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this,
			                                   &AMGPlayerController::DoJump);
		}

		if (IA_Dodge)
		{
			EnhancedInputComponent->BindAction(IA_Dodge, ETriggerEvent::Triggered, this,
			                                   &AMGPlayerController::DoDodge);
		}

		if (IA_Sprint)
		{
			EnhancedInputComponent->BindAction(IA_Sprint, ETriggerEvent::Started, this,
			                                   &AMGPlayerController::StartSprint);

			EnhancedInputComponent->BindAction(IA_Sprint, ETriggerEvent::Completed, this,
			                                   &AMGPlayerController::StopSprint);
		}
		if (IA_Walk)
		{
			EnhancedInputComponent->BindAction(IA_Walk, ETriggerEvent::Started, this,
			                                   &AMGPlayerController::StartWalk);

			EnhancedInputComponent->BindAction(IA_Walk, ETriggerEvent::Completed, this,
			                                   &AMGPlayerController::StopWalk);
		}

		if (IA_LightAttack)
		{
			EnhancedInputComponent->BindAction(IA_LightAttack, ETriggerEvent::Triggered, this,
											   &AMGPlayerController::DoLightAttack);
		}
	}
}

void AMGPlayerController::HandleMove(const FInputActionValue& InputValue)
{
	if (PlayerChar)
	{
		const FInputActionValue::Axis2D Value = InputValue.Get<FInputActionValue::Axis2D>();
		if (GetPawn() && Value.Size() != 0.0f)
		{
			this->PlayerCameraManager;
			FRotator TargetRotation = this->GetControlRotation();

			TargetRotation.Pitch = 0;
			TargetRotation.Roll = 0;
			const FVector ForwardDir = UKismetMathLibrary::GetForwardVector(TargetRotation);
			const FVector RightDir = UKismetMathLibrary::GetRightVector(TargetRotation);
			GetPawn()->AddMovementInput(ForwardDir, Value.Y);
			GetPawn()->AddMovementInput(RightDir, Value.X);
			currentInputValue = FVector(Value.X, Value.Y, 0.0);
		}
	}
}

void AMGPlayerController::HandleLook(const FInputActionValue& InputValue)
{
	if (PlayerChar)
	{
		const auto Value = InputValue.Get<FInputActionValue::Axis2D>();
		if (Value.Size() != 0.0f)
		{
			AddPitchInput(Value.Y);
			AddYawInput(Value.X);
		}
	}
}

void AMGPlayerController::DoJump()
{
	return;
	if (PlayerChar)
	{
		PlayerChar->Jump();
	}
}

void AMGPlayerController::DoDodge()
{
}

void AMGPlayerController::StartSprint()
{
	bPressedSprint = true;
}

void AMGPlayerController::StopSprint()
{
	bPressedSprint = false;
}

void AMGPlayerController::StartWalk()
{
	bPressedWalk = true;
}

void AMGPlayerController::StopWalk()
{
	bPressedWalk = false;
}

void AMGPlayerController::DoLightAttack()
{
	if(CombatSystemComp)
	{
		CombatSystemComp->AddInputToBuffer(EInputKey::LightAttack);
	}
}

void AMGPlayerController::DoHeavyAttack()
{
}

void AMGPlayerController::DoChargeAttack()
{
}

void AMGPlayerController::DoSkillAttack()
{
}
