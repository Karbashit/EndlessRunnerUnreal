// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PrimaryObjectBase.h"
#include "GameFramework/GameModeBase.h"
#include "Misc/CoreDelegates.h"
#include "TutorialProject2GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIALPROJECT2_API ATutorialProject2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()


public:
	ATutorialProject2GameModeBase();
	virtual void BeginPlay() override;

	APlayerController* Player2Controller;

	int score = 0;
	
};
