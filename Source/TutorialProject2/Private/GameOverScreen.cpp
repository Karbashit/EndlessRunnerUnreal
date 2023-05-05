// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverScreen.h"

#include "TutorialProject2/TutorialProject2GameModeBase.h"

void UGameOverScreen::NativeConstruct() {
	Super::NativeConstruct();
	RestartBtn = Cast<UButton>(GetWidgetFromName(TEXT("RestartBtn")));
	SubmitBtn = Cast<UButton>(GetWidgetFromName(TEXT("SubmitBtn")));
	TextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("TextBox")));
	FinalScoreText = Cast<UTextBlock>(GetWidgetFromName(TEXT("FinalScoreText")));

	RestartBtn->OnClicked.AddDynamic(this, &UGameOverScreen::OnPressRestart);
	SubmitBtn->OnClicked.AddDynamic(this, &UGameOverScreen::OnPressSubmit);
	
}

void UGameOverScreen::OnPressSubmit() {
	FLeaderboardItem NewRow;
	NewRow.PlayerName = TextBox->Text.ToString();
	ATutorialProject2GameModeBase* GameMode = Cast<ATutorialProject2GameModeBase>(UGameplayStatics::GetGameMode(this));
	NewRow.Score = FString::FromInt(GameMode->score);
	TArray<FName> RowNames = LeaderboardDataTable->GetRowNames();
	int32 NumRowsPlusOne = RowNames.Num() + 1;
	FName RowName = FName(FString::FromInt(NumRowsPlusOne));
	LeaderboardDataTable->AddRow(RowName, NewRow);
	UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false);
}

void UGameOverScreen::OnPressRestart() {
	UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false);
}

void UGameOverScreen::SetText() {
	ATutorialProject2GameModeBase* GameMode = Cast<ATutorialProject2GameModeBase>(UGameplayStatics::GetGameMode(this));
	FinalScoreText->SetText(FText::FromString("Your final score is: " + FString::FromInt(GameMode->score)));
}
