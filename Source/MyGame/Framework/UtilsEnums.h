// The copyright of this project belongs to Kane.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType, meta = (Bitflags))
enum class EMovementState:uint8
{
	EMS_None = 0 UMETA(DisplayName = "None"),
	EMS_Ground UMETA(DisplayName = "None"),
	EMS_Jump UMETA(DisplayName = "Jump"),
	EMS_Fly UMETA(DisplayName = "Fly"),
	EMS_Falling UMETA(DisplayName = "Falling"),
};

UENUM(BlueprintType, meta = (Bitflags))
enum class ELocomotionState:uint8
{
	ELS_None = 0 UMETA(DisplayName = "None"),
	ELS_Idle UMETA(DisplayName = "Idle"),
	ELS_Walk UMETA(DisplayName = "Walk"),
	ELS_Jog UMETA(DisplayName = "Jog"),
	ELS_Sprint UMETA(DisplayName = "Sprint"),
};



/*
 * 输入指令
 */
UENUM(BlueprintType)
enum class EInputKey :uint8
{
	None = 0 UMETA(Hidden, DisplayName = "None"),
	/**
	 * @brief 轻攻击
	*/
	LightAttack,
	/**
	 * @brief 重攻击
	*/
	HeavyAttack,
	/**
	 * @brief 跳跃
	*/
	Jump,
	/**
	 * @brief 闪避
	*/
	Dodge,
};

/*
 * 输入方向
 */
UENUM(BlueprintType)
enum class EInputDirection :uint8
{
	EID_None = 0 UMETA(Hidden, DisplayName = "None"),
	EID_Front	 UMETA(DisplayName = "Front"),
	EID_Back	 UMETA(DisplayName = "Back"),
	EID_Left	 UMETA(DisplayName = "Left"),
	EID_Right	 UMETA(DisplayName = "Right"),
};

/*
 * 角色状态
 */
UENUM(BlueprintType)
enum class ECharacterState :uint8
{
	None = 0 UMETA(Hidden, DisplayName = "None"),
	/**
	 * @brief 待机
	*/
	Idle,
	/**
	  * @brief 激活技能
	*/
	Casting,
	/**
	 * @brief 受击
	*/
	Hitting,
	/**
	 * @brief 眩晕
	*/
	Stun,
	/**
	 * @brief 闪避
	*/
	Dodge,
	/**
	 * @brief 跳跃
	*/
	Jump,
	/**
	 * @brief 死亡
	*/
	Death,
	/**
	 * @brief 弹反
	*/
	Parring,
	/**
	 * @brief 被弹反
	*/
	Parried,
};

/*
 * 受击类型
 */
UENUM(BlueprintType)
enum class EHitType :uint8
{
	EHit_None = 0 UMETA(Hidden, DisplayName = "None"),
	/**
	 * @brief 普通受击
	*/
	EHit_Normal UMETA(DisplayName = "Normal"),
	/**
	 * @brief 击退
	*/
	EHit_KnockBack UMETA(DisplayName = "KnockBack"),
	/**
	 * @brief 击飞
	*/
	EHit_KnockOff UMETA(DisplayName = "KnockOff"),
	/**
	 * @brief 击倒
	*/
	EHit_KnockDown UMETA(DisplayName = "KnockDown"),
};
