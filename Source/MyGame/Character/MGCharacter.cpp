// The copyright of this project belongs to Kane.


#include "MGCharacter.h"

#include "Combat/CharacterStatusComponent.h"
#include "Combat/CombatSystemComponent.h"

AMGCharacter::AMGCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	CombatSystemComp = CreateDefaultSubobject<UCombatSystemComponent>(TEXT("CombatSystemComp"));
	StatusComp = CreateDefaultSubobject<UCharacterStatusComponent>(TEXT("StatusComp"));
}

void AMGCharacter::BeginPlay()
{
	Super::BeginPlay();
	CombatSystemComp->Init(GetMesh(), GetCharacterMovement(), StatusComp);
}

void AMGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
