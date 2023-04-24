// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "EnhancedInputSubsystems.h"
#include "UInputSystem.h"
#include "PauseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIALPROJECT2_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	void OnPause();
	void OnSelect(float value, APlayerController* pc);
	void SwitchInput(UEnhancedInputLocalPlayerSubsystem* SubSystem, UInputSystem* InputSystem);
	void CacheSubAndInput(UEnhancedInputLocalPlayerSubsystem* SubSystem, UInputSystem* InputSystem);
	
	UFUNCTION()
	void OnResumeButtonPress();
	
	UFUNCTION()
	void OnQuitButtonPress();

	UPROPERTY(meta = (BindWidget))
	class UButton* ResumeButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

private:
	UPROPERTY(meta = (BindWidget))
	class UWidget* UI_PauseMenu;

	bool paused = false;

	UEnhancedInputLocalPlayerSubsystem* CachedSubSystem;
	UInputSystem* CachedInputSystem;
	
};
