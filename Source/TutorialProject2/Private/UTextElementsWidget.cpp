// Fill out your copyright notice in the Description page of Project Settings.


#include "UTextElementsWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"

void UTextElementsWidget::NativeConstruct(){
	Super::NativeConstruct();

	UI_TextElements = Cast<UWidget>(GetWidgetFromName(TEXT("UI_TextElements")));
	Time = Cast<UTextBlock>(GetWidgetFromName(TEXT("Time")));
	ReadyText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ReadyText")));

	Player1Life1 = Cast<UImage>(GetWidgetFromName(TEXT("Player1Life1")));
	Player1Life2 = Cast<UImage>(GetWidgetFromName(TEXT("Player1Life2")));
	Player1Life3 = Cast<UImage>(GetWidgetFromName(TEXT("Life3Player33")));

	Player2Life1 = Cast<UImage>(GetWidgetFromName(TEXT("Player2Life1")));
	Player2Life2 = Cast<UImage>(GetWidgetFromName(TEXT("Player2Life2")));
	Player2Life3 = Cast<UImage>(GetWidgetFromName(TEXT("Player2Life3")));
	
	UE_LOG(LogTemp, Display, TEXT("UI TEXT Widget Constructed"));
}

void UTextElementsWidget::SetTimer(int MSec, int Sec, int Min)
{
	if(Time)
	{
		FString sMin, sSec, sMSec;
		if(Min<10)
		{
			sMin = "0" + FString::FromInt(Min);
		}
		else
		{
			sMin = FString::FromInt(Min);
		}

		if(Sec<10)
		{
			sSec = "0" + FString::FromInt(Sec);
		}
		else
		{
			sSec = FString::FromInt(Sec);
		}

		if(MSec<10)
		{
			sMSec = "00" + FString::FromInt(MSec);
		}
		else if(MSec>9 && MSec<100)
		{
			sMSec = "0" + FString::FromInt(MSec);
		}
		else
		{
			sMSec = FString::FromInt(MSec);
		}

		FString stringFullTime = sMin + ":" + sSec + ":" + sMSec;

		Time->SetText(FText::FromString(stringFullTime));
	}
}
