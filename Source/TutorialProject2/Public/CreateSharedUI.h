// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutorialProject2/Public/UTextElementsWidget.h"
#include "Blueprint/UserWidget.h"
#include "CreateSharedUI.generated.h"

class UTextElementsWidget;

UCLASS()
class TUTORIALPROJECT2_API ACreateSharedUI : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACreateSharedUI();

	UPROPERTY()
	UUserWidget* UITextWidgetInstance;
	
	UTextElementsWidget* UITextWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<UUserWidget> UITextWidgetClass;


	float TimeFromStart = 0;
	bool GameStarted = false;

	float TotalTime = 0;

	void RemoveLife(int32 PlayerIndex);
	int Player1Life = 3;
	int Player2Life = 3;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
