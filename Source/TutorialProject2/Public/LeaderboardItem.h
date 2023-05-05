// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LeaderboardItem.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct TUTORIALPROJECT2_API FLeaderboardItem : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString PlayerName;
	
	UPROPERTY()
	FString Score;
};
