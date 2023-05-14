// The copyright of this project belongs to Kane.


#include "Combat/Action.h"

#include "CombatSystemComponent.h"

UAction::UAction(): Input(EInputKey::LightAttack), AnimMontage(nullptr), FinalState(ECharacterState::Casting),
                    Damage(5.0f), AP(30.0f), bCanBeDamage(true), bCanBeHit(true)
{
}

void UAction::Initialized(UCombatSystemComponent* _combatSystemComp, UCharacterStatusComponent* _StatusComponent)
{
	this->combatSystemComp = _combatSystemComp;
	this->StatusComponent = _StatusComponent;
}

void UAction::StartCasting()
{
	BP_StartCasting();
}

void UAction::StopCasting()
{
	BP_StopCasting();
}

void UAction::PlayAnim()
{
	if(combatSystemComp)
		combatSystemComp->PlayHighPriorityAnim(AnimMontage);
}

bool UAction::CanBeCasting()
{
	return true;
}

bool UAction::BP_CanBeCasting_Implementation()
{
	return true;
}

UWorld* UAction::GetWorld() const
{
	const AActor* outerActor = Cast<AActor>(GetOuter());
	if (outerActor)
		return outerActor->GetWorld();
	return nullptr;
}

UIdleAction::UIdleAction()
{
}

void UIdleAction::StartCasting()
{
	Super::StartCasting();
}

void UIdleAction::StopCasting()
{
	Super::StopCasting();
}
