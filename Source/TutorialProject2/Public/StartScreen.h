// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LeaderboardItem.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "StartScreen.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIALPROJECT2_API UStartScreen : public UUserWidget
{
	GENERATED_BODY()


public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	UButton* PlayBtn;
	
	UFUNCTION()
	void OnPressPlay();

	FLeaderboardItem* LeaderboardRow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="DataTable")
	UDataTable* LeaderboardDataTable;

	void OperationForEachVoid();

	UPROPERTY(meta = (BindWidget))
	UTextBlock* p1name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* p2name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* p3name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* p4name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* p5name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* p6name;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* p1score;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* p2score;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* p3score;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* p4score;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* p5score;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* p6score;

	FString GetName();
	FString GetScore();
};
