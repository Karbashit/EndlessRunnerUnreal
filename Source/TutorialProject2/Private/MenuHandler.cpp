// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHandler.h"

#include "GameOverScreen.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMenuHandler::AMenuHandler()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMenuHandler::PlayerDead() {
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->bShowMouseCursor = true;
	GameOverMenuInstance->SetVisibility(ESlateVisibility::Visible);
	PlayerController->SetPause(true);
}

void AMenuHandler::BeginPlay()
{
	Super::BeginPlay();
	StartMenuInstance = CreateWidget<UUserWidget>(GetWorld(), StartMenuClass);
	if (StartMenuInstance != nullptr) {
		StartMenuInstance->AddToViewport();
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		StartMenuInstance->SetOwningPlayer(PlayerController);
	}

	GameOverMenuInstance = CreateWidget<UUserWidget>(GetWorld(), GameOverMenuClass);
	if (GameOverMenuInstance != nullptr) {
		GameOverMenuInstance->AddToViewport();
		GameOverMenuInstance->SetVisibility(ESlateVisibility::Hidden);
	}


	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->bShowMouseCursor = true;
	PlayerController->SetPause(true);
}

void AMenuHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

