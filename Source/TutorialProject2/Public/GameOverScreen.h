// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LeaderboardItem.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Engine/DataTable.h"
#include "GameOverScreen.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIALPROJECT2_API UGameOverScreen : public UUserWidget {
	GENERATED_BODY()
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* RestartBtn;

	UPROPERTY(meta = (BindWidget))
	UButton* SubmitBtn;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* TextBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* FinalScoreText;
	
	UFUNCTION()
	void OnPressSubmit();

	UFUNCTION()
	void OnPressRestart();

	FOnVisibilityChangedEvent OnVisibilityChanged;

	void HandleVisibilityChanged(ESlateVisibility NewVisibility);

public:
	FLeaderboardItem* LeaderboardRow;

	void SetText();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="DataTable")
	UDataTable* LeaderboardDataTable;
};
