// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "Windows/WindowsWindow.h"
#include "Windows.h"
#include "Components/Image.h"
#include "UTextElementsWidget.generated.h"

UCLASS()
class TUTORIALPROJECT2_API UTextElementsWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	void SetTimer(int MSec, int Sec, int Min);

	FString SecondsPassed;
	
	UPROPERTY()
	UImage* Player1Life1;

	UPROPERTY()
	UImage* Player1Life2;

	UPROPERTY()
	UImage* Player1Life3;

	UPROPERTY()
	UImage* Player2Life1;

	UPROPERTY()
	UImage* Player2Life2;

	UPROPERTY()
	UImage* Player2Life3;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Time;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ReadyText;

	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* TimeText;

	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* ReadyFade;

	void RemoveLife(int32 PlayerIndex);

	

private:
	UPROPERTY(meta = (BindWidget))
	class UWidget* UI_TextElements;
};