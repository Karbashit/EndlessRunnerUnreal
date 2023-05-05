// Fill out your copyright notice in the Description page of Project Settings.


#include "StartScreen.h"

void UStartScreen::NativeConstruct() {
	Super::NativeConstruct();
	PlayBtn = Cast<UButton>(GetWidgetFromName(TEXT("PlayBtn")));
	PlayBtn->OnClicked.AddDynamic(this, &UStartScreen::OnPressPlay);

	FString ContextString;

	TArray<UTextBlock*> PlayerNames;
	PlayerNames.Add(p1name);
	PlayerNames.Add(p2name);
	PlayerNames.Add(p3name);
	PlayerNames.Add(p4name);
	PlayerNames.Add(p5name);
	PlayerNames.Add(p6name);

	TArray<UTextBlock*> PlayerScores;
	PlayerScores.Add(p1score);
	PlayerScores.Add(p2score);
	PlayerScores.Add(p3score);
	PlayerScores.Add(p4score);
	PlayerScores.Add(p5score);
	PlayerScores.Add(p6score);

	TArray<FName> RowNames = LeaderboardDataTable->GetRowNames();
	int32 NumRows = RowNames.Num();
	if(NumRows > 0 && NumRows <=5) {
		for (int i = 1; i <= NumRows; i++) {
			FName tempName = FName(FString::FromInt(i));
			LeaderboardRow = LeaderboardDataTable->FindRow<FLeaderboardItem>(tempName, ContextString);
			if (LeaderboardRow != nullptr) {
			FString PlayerName = LeaderboardRow->PlayerName;
			FString PlayerScore = LeaderboardRow->Score;
			PlayerNames[i - 1]->SetText(FText::FromString(PlayerName));
			PlayerScores[i - 1]->SetText(FText::FromString(PlayerScore));
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("LEADERBOARDROW NULL"));
			}
		}
	}
}

void UStartScreen::OnPressPlay() {
	UE_LOG(LogTemp, Warning, TEXT("Press Play"));
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->bShowMouseCursor = false;
	PlayerController->SetPause(false);
	SetVisibility(ESlateVisibility::Hidden);
}

void UStartScreen::OperationForEachVoid() {
}
