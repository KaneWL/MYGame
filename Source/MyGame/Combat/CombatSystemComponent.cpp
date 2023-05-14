// The copyright of this project belongs to Kane.


#include "Combat/CombatSystemComponent.h"

#include "Action.h"
#include "Framework/UtilsStruct.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Helper/DebugHelper.h"


UCombatSystemComponent::UCombatSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UCombatSystemComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UCombatSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UCombatSystemComponent::Init(USkeletalMeshComponent* _meshComp, UCharacterMovementComponent* _movementComp, UCharacterStatusComponent* _StatusComponent)
{
	this->meshComp = _meshComp;
	if (meshComp)
	{
		this->animInstance = meshComp->GetAnimInstance();
		if (animInstance)
			animInstance->OnMontageEnded.AddDynamic(this, &UCombatSystemComponent::OnMontageEnded);
	}
	this->movementComp = _movementComp;
	this->StatusComp = _StatusComponent;

	// 初始化技能
	if (DT_Actions)
	{
		TArray<FName>RowNameArr = DT_Actions->GetRowNames();
		for (auto& rowName : RowNameArr)
		{
			const FAttackMove* AM = DT_Actions->FindRow<FAttackMove>(rowName, TEXT("None"));
			if (!AM || !AM->bEnable)continue;
			FString skillId;// 字符串左边,当前技能id
			FString preSkillId;// 字符串右边,上一个技能id
			FString rowNameStr = rowName.ToString();
			if (!rowNameStr.Split("<", &skillId, &preSkillId, ESearchCase::IgnoreCase))
			{
				DebugHeader::Debug(FColor::Red) << "skill is not set <" << rowNameStr << DebugHeader::Endl();
				continue;
			}
			UAction* skillIns = nullptr;
			if (AddSkill(AM->SkillTemplate, skillIns))
			{
				// 初始化数据
				skillIns->Id = FName(skillId);
				skillIns->PreSkillsId.Add(FName(preSkillId));
				skillIns->Input = AM->Input;
				skillIns->AnimMontage = AM->AnimMontage;
				skillIns->FromState = AM->FromState;
				skillIns->FinalState = AM->FinalState;
				skillIns->Damage = AM->Damage;
				skillIns->AP = AM->AP;
				skillIns->bCanBeDamage = AM->bCanBeDamage;
				skillIns->bCanBeHit = AM->bCanBeHit;
				DebugHeader::Debug(FColor::Red) << "Add skill: " << rowNameStr << DebugHeader::Endl();
			}
		}
	}
	else
	{
		DebugHeader::Debug(FColor::Red) << "Skill Data Table is not set!" << GetOwner() << DebugHeader::Endl();
	}
	this->CurrentState = ECharacterState::Idle;
	ResetState();
}

void UCombatSystemComponent::AddInputToBuffer(EInputKey key)
{
	if (bEnableInputBuffer)
	{
		this->StoredKey.Add(key);
		if (CurrentState == ECharacterState::Idle)
			EndInput();
	}
	else
	{
		DebugHeader::Debug() << "invalid input." << GetOwner() << DebugHeader::Endl();
	}
}


void UCombatSystemComponent::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	DebugHeader::Debug() << "On Montage Ended." << GetOwner() << DebugHeader::Endl();
	if(!bInterrupted)
		ResetState();
}

float UCombatSystemComponent::PlayAnim(UAnimMontage* MontageToPlay)
{
	if (!animInstance)
	{
		DebugHeader::Debug() << "Anim Instance is not set." << GetOwner() << DebugHeader::Endl();
		return 0.0f;
	}
	if (!MontageToPlay)
	{
		DebugHeader::Debug() << "Montage to play is not set." << GetOwner() << DebugHeader::Endl();
		return 0.0f;
	}
	if (!animInstance->IsAnyMontagePlaying())
	{
		DebugHeader::Debug() << "has montage playing." << GetOwner() << DebugHeader::Endl();
		return 0.0f;
	}
	currentMontage = MontageToPlay;
	return  animInstance->Montage_Play(MontageToPlay);
}

float UCombatSystemComponent::PlayHighPriorityAnim(UAnimMontage* MontageToPlay)
{
	if (!animInstance)
	{
		DebugHeader::Debug() << "Anim Instance is not set." << GetOwner() << DebugHeader::Endl();
		return 0.0f;
	}
	if (!MontageToPlay)
	{
		DebugHeader::Debug() << "Montage to play is not set." << GetOwner() << DebugHeader::Endl();
		ResetState();
		return 0.0f;
	}
	currentMontage = MontageToPlay;
	return  animInstance->Montage_Play(MontageToPlay);
}



void UCombatSystemComponent::StartInput()
{
	this->bEnableInputBuffer = true;
}

void UCombatSystemComponent::EndInput()
{
	this->bEnableInputBuffer = false;
	ConsumedStoredKey();
//this->StoredKey.RemoveAllSwap(EInputKey::None);
	StoredKey.Empty();
}

void UCombatSystemComponent::ConsumedStoredKey()
{
	// 检查ground  air  （运动状态）
	// 检查摇杆输入
	// 检查当前动作可转换的有效指令

	//
	// 获取当前状态/技能动作id
	const FName currentStateId(GetCurrentStateOrSkillId());
	for (auto& skill : ActionsTree)
	{
		// 检查节点
		if (skill && skill->PreSkillsId.Contains(currentStateId))
		{
			// 检查输入
			if (!skill->CanBeCasting())continue;
			if (!this->StoredKey.Contains(skill->Input))continue;
			skill->StartCasting();
			return;
		}
	}
	ResetState();
}

bool UCombatSystemComponent::AddSkill(TSubclassOf<UAction> ActionClass, UAction*& ActionIns)
{
	UAction* skill = NewObject<UAction>(GetOwner(), ActionClass);
	if (!skill)return false;
	skill->Initialized(this, StatusComp);
	ActionIns = skill;
	ActionsTree.Add(skill);
	return true;
}

void UCombatSystemComponent::StartCasting(FName Id)
{
	for (const auto& skill : ActionsTree)
	{
		if (skill && skill->GetSkillId() == Id)
		{
			skill->StartCasting();
			return;
		}
	}
}

void UCombatSystemComponent::StopCasting(FName Id)
{
	for (const auto& skill : ActionsTree)
	{
		if (skill && skill->GetSkillId() == Id)
		{
			skill->StopCasting();
			return;
		}
	}
}

void UCombatSystemComponent::ResetState()
{
	if (CurrentState == ECharacterState::Death || CurrentState == ECharacterState::Hitting)return;
	if (movementComp && movementComp->IsFalling())
	{
		CurrentState = ECharacterState::Jump;
	}
	else
	{
		CurrentState = ECharacterState::Idle;
	}

	bEnableInputBuffer = true;
	currentMontage = nullptr;
	CurrentAction = nullptr;
	DebugHeader::Debug() << " reset " << bEnableInputBuffer << " " << GetOwner() << DebugHeader::Endl();
}

FName UCombatSystemComponent::GetCurrentStateOrSkillId()
{
	FName currentStateId;
	if (CurrentAction)
	{
		// 如果有技能存在 则获取技能id作为状态id
		currentStateId = CurrentAction->GetSkillId();
	}
	else
	{
		// 无技能存在 获取角色状态 作为id

		if (movementComp && movementComp->IsFalling())
		{
			currentStateId = "Jump";
		}
		else
		{
			currentStateId = "Idle";
		}

	}
	return currentStateId;
}
