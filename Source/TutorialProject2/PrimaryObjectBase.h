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

UCLASS(Config=Game)
class TUTORIALPROJECT2_API APrimaryObjectBase : public ACharacter {
	GENERATED_BODY()

public:
	UEnhancedInputComponent* PEI;
	
	UPROPERTY(EditAnywhere, Category="InputMap")
	UInputSystem* InputSystemComponent;
	
	UPROPERTY(EditAnywhere, Category="Body")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category="MovementProperties")
	UMovement* movementComponent;

	// UPROPERTY(EditAnywhere, Category="UCameraMovement")
	// UCameraMovement* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	int32 Player1Life = 3;
	int32 Player2Life = 3;

	UPROPERTY()
	UUserWidget* PauseWidgetInstance;

	UPauseMenuWidget* PauseWidget;
	
	APrimaryObjectBase();

	FVector2D moveInput;

	void RemoveLife();

	void TurnLeft(const FInputActionValue& Value);
	void TurnRight(const FInputActionValue& Value);

	void MoveLeftP2(const FInputActionValue& Value);
	void MoveRightP2(const FInputActionValue& Value);
	
	void MoveLeft(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void BoostStart(const FInputActionValue& Value);
	void BoostEnd(const FInputActionValue& Value);
	void Toggle(const FInputActionValue& Value);
	void PausedSelect(const FInputActionValue& Value);

	void MovePlayer(FVector fvector);

	UPROPERTY(VisibleAnywhere)
	int32 PlayerIndex;

	bool Paused = false;
	bool ButtonThresh = false;

	float jumpCooldown = 2;
	float jumpTimer;
	
	float boostTimer;
	
	bool canDash;
	bool isInAir;
	bool GroundCheck();
	
	TArray<FVector> Player1Positions;
	TArray<FVector> Player2Positions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerPositions")
	FVector Player1Position1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerPositions")
	FVector Player1Position2;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerPositions")
	FVector Player1Position3;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerPositions")
	FVector Player2Position1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerPositions")
	FVector Player2Position2;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerPositions")
	FVector Player2Position3;
	
	FVector CurrentPosition;
	int PlayerPositionIndex;

	TArray<FVector> GetCorrectArray(int playerNumbner);


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