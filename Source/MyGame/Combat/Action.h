// The copyright of this project belongs to Kane.

#pragma once

#include "CoreMinimal.h"
#include "Framework/UtilsEnums.h"
#include "UObject/NoExportTypes.h"
#include "Action.generated.h"

class UAnimInstance;
class USkeletalMeshComponent;
class UCharacterStatusComponent;
class UCharacterMovementComponent;


UCLASS(Blueprintable)
class MYGAME_API UAction : public UObject
{
	GENERATED_BODY()
public:

	UAction();
	UFUNCTION(BlueprintCallable, Category = "Skill")
		void Initialized(UCombatSystemComponent* _combatSystemComp, UCharacterStatusComponent* _StatusComponent);
	UFUNCTION(BlueprintPure, Category = "Skill")
		FName GetSkillId() { return Id; }
	UFUNCTION(BlueprintPure, Category = "Skill")
		AActor* GetOwner() { return  Cast<AActor>(GetOuter()); }
	UFUNCTION(BlueprintPure, Category = "Skill")
		APawn* GetCasterPawn() { return Cast<APawn>(GetOuter()); }

	
	UFUNCTION(BlueprintCallable, Category = "Skill")
		virtual void StartCasting();
	UFUNCTION(BlueprintCallable, Category = "Skill")
		virtual void StopCasting();

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "StartCasting", Category = "Action")
		void BP_StartCasting();
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "StopCasting", Category = "Action")
		void BP_StopCasting();

	UFUNCTION(BlueprintCallable, Category = "Skill")
		void PlayAnim();

	UFUNCTION(BlueprintCallable, Category = "Skill")
		bool CanBeCasting();
	UFUNCTION(BlueprintNativeEvent, Category = "Skill")
		bool BP_CanBeCasting();
public:

	virtual class UWorld* GetWorld() const override;;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UCombatSystemComponent* combatSystemComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UCharacterStatusComponent* StatusComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName Id;
	// 技能树节点
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FName>PreSkillsId;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EInputKey Input;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* AnimMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<ECharacterState> FromState;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ECharacterState FinalState;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Damage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AP;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 bCanBeDamage : 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 bCanBeHit : 1;


private:
};

UCLASS()
class MYGAME_API UIdleAction : public UAction
{
	GENERATED_BODY()
public:
	UIdleAction();
	virtual void StartCasting()override;
	virtual void StopCasting()override;
};
