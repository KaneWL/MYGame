// The copyright of this project belongs to Kane.

#pragma once

#include "CoreMinimal.h"
#include "UtilsEnums.h"
#include "Combat/Action.h"
#include "Engine/DataTable.h"
#include "UtilsStruct.generated.h"

/**
 * 
 */
class MYGAME_API UtilsStruct
{
public:
	UtilsStruct();
	~UtilsStruct();
};

USTRUCT(BlueprintType)
struct MYGAME_API FAttackMove :public FTableRowBase
{
	GENERATED_BODY()
public:
	FAttackMove(): bEnable(true), Input(EInputKey::LightAttack), SkillTemplate(UAction::StaticClass()),
	AnimMontage(nullptr), FinalState(ECharacterState::Casting),
	Damage(0), AP(0), bCanBeDamage(true), bCanBeHit(true)
	{
	}
	;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bEnable : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
	EInputKey Input;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	TSubclassOf<UAction>SkillTemplate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	TArray<ECharacterState> FromState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	ECharacterState FinalState;

	// dmg
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DMG")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DMG")
	float AP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DMG")
	uint8 bCanBeDamage : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DMG")
	uint8 bCanBeHit : 1;
};