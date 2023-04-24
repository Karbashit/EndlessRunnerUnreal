// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "TutorialProject2/Public/UMovement.h"
#include "TutorialProject2/Public/UInputSystem.h"
#include "TutorialProject2/Public/PauseMenuWidget.h"
#include "TutorialProject2/Public/UTextElementsWidget.h"
#include "EnhancedInput/Public/InputActionValue.h"
#include "GameFramework/SpringArmComponent.h"
#include "Blueprint/UserWidget.h"
#include "PrimaryObjectBase.generated.h"

class UMovement;
class UInputSystem;
class UCameraMovement;
class UPauseMenuWidget;
class UTextElementsWidget;

UCLASS(Config=Game)
class TUTORIALPROJECT2_API APrimaryObjectBase : public APawn {
	GENERATED_BODY()

public:
	UEnhancedInputComponent* PEI;
	
	UPROPERTY(EditAnywhere, Category="InputMap")
	UInputSystem* InputSystemComponent;
	
	UPROPERTY(EditAnywhere, Category="Body")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category="MovementProperties")
	UMovement* movementComponent;

	UPROPERTY(EditAnywhere, Category="UCameraMovement")
	UCameraMovement* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<UUserWidget> UITextWidgetClass;

	

	UPROPERTY()
	UUserWidget* PauseWidgetInstance;

	UPROPERTY()
	UUserWidget* UITextWidgetInstance;

	UPauseMenuWidget* PauseWidget;
	UTextElementsWidget* UITextWidget;
	
	APrimaryObjectBase();

	FVector2D moveInput;

	void TurnLeft(const FInputActionValue& Value);
	void TurnRight(const FInputActionValue& Value);
	void MoveLeft(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void BoostStart(const FInputActionValue& Value);
	void BoostEnd(const FInputActionValue& Value);
	void Toggle(const FInputActionValue& Value);
	void PausedSelect(const FInputActionValue& Value);

	void MovePlayer(FVector fvector);

	bool Paused = false;
	bool ButtonThresh = false;

	float jumpCooldown = 2;
	float jumpTimer;

	float TotalTime = 0;
	
	float TimeFromStart = 0;
	bool GameStarted = false;
	
	float boostTimer;
	
	bool canDash;
	bool isInAir;
	bool GroundCheck();
	
	TArray<FVector> PlayerPositions;
	FVector PlayerPosition1;
	FVector PlayerPosition2;
	FVector PlayerPosition3;
	FVector CurrentPosition;
	int PlayerPositionIndex;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime);

private:

	APlayerController* PlayerController;
	UEnhancedInputLocalPlayerSubsystem* SubSystem;
};