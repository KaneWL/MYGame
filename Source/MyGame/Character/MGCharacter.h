// The copyright of this project belongs to Kane.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MGCharacter.generated.h"

class UCharacterStatusComponent;
class UCombatSystemComponent;

UCLASS()
class MYGAME_API AMGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMGCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCombatSystemComponent* CombatSystemComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCharacterStatusComponent* StatusComp;
};
