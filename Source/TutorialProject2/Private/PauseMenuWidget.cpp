// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"

void UPauseMenuWidget::NativeConstruct() {
	Super::NativeConstruct();

	UI_PauseMenu = Cast<UWidget>(GetWidgetFromName(TEXT("UI_PauseMenu")));
	ResumeButton = Cast<UButton>(GetWidgetFromName(TEXT("ResumeButton")));
	QuitButton = Cast<UButton>(GetWidgetFromName(TEXT("QuitButton")));
	ResumeButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnResumeButtonPress);
	QuitButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnQuitButtonPress);

	UI_PauseMenu->SetVisibility(ESlateVisibility::Hidden);
	UE_LOG(LogTemp, Display, TEXT("Pause Widget Constructed"));

}

void UPauseMenuWidget::OnPause() {
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (UI_PauseMenu != nullptr) {
		if (UI_PauseMenu->IsVisible()) {
			UE_LOG(LogTemp, Display, TEXT("Un-Pause"));
			UI_PauseMenu->SetVisibility(ESlateVisibility::Hidden);
			PlayerController->SetPause(false);

		}
		else {
			UE_LOG(LogTemp, Display, TEXT("Pause"));
			UI_PauseMenu->SetVisibility(ESlateVisibility::Visible);
			PlayerController->SetPause(true);
		}
	}
}

void UPauseMenuWidget::OnSelect(float value, APlayerController* pc) {
	if (value < -0.5f) {
		UE_LOG(LogTemp, Display, TEXT("Resume Selected"));
		ResumeButton->SetUserFocus(pc);
	}
	else if (value > 0.5f) {
		UE_LOG(LogTemp, Display, TEXT("Quit Selected"));
		QuitButton->SetUserFocus(pc);
	}
}

void UPauseMenuWidget::SwitchInput(UEnhancedInputLocalPlayerSubsystem* SubSystem, UInputSystem* InputSystem) {

	paused = !paused;
	if (paused) {
		SubSystem->RemoveMappingContext(InputSystem->InputMappingMoveLeft);
		SubSystem->RemoveMappingContext(InputSystem->InputMappingMoveRight);
		SubSystem->AddMappingContext(InputSystem->PauseMenuControls, 0);
	}
	else {
		SubSystem->RemoveMappingContext(InputSystem->PauseMenuControls);
		SubSystem->AddMappingContext(InputSystem->InputMappingMoveLeft, 0);
		SubSystem->AddMappingContext(InputSystem->InputMappingMoveRight, 0);
	}
}

void UPauseMenuWidget::CacheSubAndInput(UEnhancedInputLocalPlayerSubsystem* SubSystem, UInputSystem* InputSystem) {
	CachedSubSystem = SubSystem;
	CachedInputSystem = InputSystem;
}

void UPauseMenuWidget::OnResumeButtonPress() {
	UE_LOG(LogTemp, Display, TEXT("Un-Pause"));
	CachedSubSystem->RemoveMappingContext(CachedInputSystem->PauseMenuControls);
	CachedSubSystem->AddMappingContext(CachedInputSystem->InputMappingMoveLeft, 0);
	CachedSubSystem->AddMappingContext(CachedInputSystem->InputMappingMoveRight, 0);
	OnPause();
}

void UPauseMenuWidget::OnQuitButtonPress() {
	//FGenericPlatformMisc::RequestExit(false);
}
