// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LeaderboardItem.h"
#include "GameFramework/Actor.h"
#include "StartScreen.h"
#include "MenuHandler.generated.h"

UCLASS()
class TUTORIALPROJECT2_API AMenuHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMenuHandler();
	UPROPERTY()
	UUserWidget* StartMenuInstance;
	
	UStartScreen* UIStartMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetClasses")
	TSubclassOf<UUserWidget> StartMenuClass;

	UPROPERTY()
	UUserWidget* GameOverMenuInstance;
	
	UStartScreen* UIGameOverMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetClasses")
	TSubclassOf<UUserWidget> GameOverMenuClass;
	
	void PlayerDead();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
