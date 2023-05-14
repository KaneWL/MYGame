// The copyright of this project belongs to Kane.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "CombatSystemComponent.generated.h"


class UAction;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYGAME_API UCombatSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCombatSystemComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** 初始化*/
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Init(USkeletalMeshComponent* _meshComp, UCharacterMovementComponent* _movementComp, UCharacterStatusComponent* _StatusComponent);

	/** 输入*/
	UFUNCTION(BlueprintCallable, Category = "Combat|Input")
	void AddInputToBuffer(EInputKey key);
	
protected:
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	/**
	 * @brief 尝试播放动画
	 * @param MontageToPlay 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat|Anim")
	float PlayAnim(UAnimMontage* MontageToPlay);
	/**
	 * @brief 强制播放动画
	 * @param MontageToPlay 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat|Anim")
	float PlayHighPriorityAnim(UAnimMontage* MontageToPlay);

	void StartInput();
	void EndInput();
	void ConsumedStoredKey();

	/** 技能*/
	UFUNCTION(BlueprintCallable, Category = "Combat|Skill")
	bool AddSkill(TSubclassOf<UAction>ActionClass, UAction*& ActionIns);
	UFUNCTION(BlueprintCallable, Category = "Combat|Skill")
	void StartCasting(FName Id);
	UFUNCTION(BlueprintCallable, Category = "Combat|Skill")
	void StopCasting(FName Id);

	UFUNCTION(BlueprintCallable, Category = "Combat|State")
	void SetCurrentState(ECharacterState state) { this->CurrentState = state; }
	UFUNCTION(BlueprintPure, Category = "Combat|State")
	ECharacterState GetCurrentState() const { return this->CurrentState; }
UFUNCTION()
	void ResetState();// 落地时/蒙太奇播完（非中断） 时调用

	
	FName GetCurrentStateOrSkillId();

private:
	friend class UAction;
	UAnimInstance* animInstance;
	USkeletalMeshComponent* meshComp;
	UCharacterMovementComponent* movementComp;
	UCharacterStatusComponent* StatusComp;
	UAnimMontage* currentMontage;

	UAction* CurrentAction;
	ECharacterState CurrentState;
	uint8 bEnableInputBuffer : 1;// 是否开启输入 未开启，则无效输入
	TArray<EInputKey>StoredKey;// 存储的指令
	UPROPERTY()
	TArray<UAction*>ActionsTree;// 所有的招式

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UDataTable* DT_Actions;
};
