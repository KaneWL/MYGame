// The copyright of this project belongs to Kane.


#include "System/MGGameModeBase.h"

#include "MGGameStateBase.h"
#include "MGPlayerController.h"
#include "MGPlayerState.h"
#include "Character/MGCharacter.h"

AMGGameModeBase::AMGGameModeBase()
{
	DefaultPawnClass = AMGCharacter::StaticClass();
	PlayerStateClass = AMGPlayerState::StaticClass();
	GameStateClass = AMGGameStateBase::StaticClass();
	PlayerControllerClass = AMGPlayerController::StaticClass();
}
