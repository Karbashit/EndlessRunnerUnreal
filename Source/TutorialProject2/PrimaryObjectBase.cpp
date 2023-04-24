// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimaryObjectBase.h"

#include <Windows.Media.Core.h>

#include "EnhancedInputComponent.h"
#include "PauseMenuWidget.h"
#include "UCameraMovement.h"
#include "Camera/CameraModifier.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "TutorialProject2/Public/UInputSystem.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/InputActionValue.h"
#include "EnhancedInput/Public/InputMappingContext.h"
#include "TutorialProject2/Public/PauseMenuWidget.h"
#include "TutorialProject2/Public/UTextElementsWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APrimaryObjectBase::APrimaryObjectBase() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	CameraComponent = CreateDefaultSubobject<UCameraMovement>("CameraMovement");
	movementComponent = CreateDefaultSubobject<UMovement>("UMovement");
	InputSystemComponent = CreateDefaultSubobject<UInputSystem>("UInputSystem");

	APrimaryObjectBase::SetupPlayerInputComponent(InputSystemComponent);
	StaticMeshComponent->SetSimulatePhysics(true);
	SetRootComponent(StaticMeshComponent);
	CameraComponent->SpringArmComponent->AttachToComponent(GetRootComponent(),
	                                                       FAttachmentTransformRules::KeepRelativeTransform);
	CameraComponent->CameraComponent->AttachToComponent(CameraComponent->SpringArmComponent,
	                                                    FAttachmentTransformRules::KeepRelativeTransform);
}

void APrimaryObjectBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	if (PlayerController == nullptr) PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController != nullptr) {
		if (SubSystem == nullptr)
			SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
				PlayerController->GetLocalPlayer());
		SubSystem->ClearAllMappings();
		SubSystem->AddMappingContext(InputSystemComponent->InputMappingMoveLeft, 0);
		SubSystem->AddMappingContext(InputSystemComponent->InputMappingMoveRight, 0);
		SubSystem->AddMappingContext(InputSystemComponent->InputMappingSelect, 10);
		SubSystem->AddMappingContext(InputSystemComponent->InputMappingJump, 1);
	}

	PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (PEI != nullptr) {
		PEI->BindAction(InputSystemComponent->InputMoveLeft, ETriggerEvent::Triggered, this,
		                &APrimaryObjectBase::MoveLeft);
		PEI->BindAction(InputSystemComponent->InputMoveRight, ETriggerEvent::Triggered, this,
		                &APrimaryObjectBase::MoveRight);
		PEI->BindAction(InputSystemComponent->JumpAction, ETriggerEvent::Triggered, this, &APrimaryObjectBase::Jump);
		PEI->BindAction(InputSystemComponent->BoostActionStart, ETriggerEvent::Triggered, this,
		                &APrimaryObjectBase::BoostStart);
		PEI->BindAction(InputSystemComponent->BoostActionEnd, ETriggerEvent::Triggered, this,
		                &APrimaryObjectBase::BoostEnd);
		PEI->BindAction(InputSystemComponent->ToggleAction, ETriggerEvent::Triggered, this,
		                &APrimaryObjectBase::Toggle);
		PEI->BindAction(InputSystemComponent->TurnLeftAction, ETriggerEvent::Triggered, this,
		                &APrimaryObjectBase::TurnLeft);
		PEI->BindAction(InputSystemComponent->TurnRightAction, ETriggerEvent::Triggered, this,
		                &APrimaryObjectBase::TurnRight);
		PEI->BindAction(InputSystemComponent->PauseSelect, ETriggerEvent::Triggered, this,
		                &APrimaryObjectBase::PausedSelect);
	}
}

void APrimaryObjectBase::MoveLeft(const FInputActionValue& Value) {
	if (PlayerPositionIndex > 0) {
		PlayerPositionIndex--;
		MovePlayer(PlayerPositions[PlayerPositionIndex]);
	}
	else {
		return;
	}

	// moveInput = Value.Get<FVector2D>();
	// UE_LOG(LogTemp, Display, TEXT("MoveInput Detected: X=%f, Y=%f"), moveInput.X, moveInput.Y);
}

void APrimaryObjectBase::MoveRight(const FInputActionValue& Value) {
	if (PlayerPositionIndex < 2) {
		PlayerPositionIndex++;
		MovePlayer(PlayerPositions[PlayerPositionIndex]);
	}
	else {
		return;
	}

	// moveInput = Value.Get<FVector2D>();
	// UE_LOG(LogTemp, Display, TEXT("MoveInput Detected: X=%f, Y=%f"), moveInput.X, moveInput.Y);
}

void APrimaryObjectBase::TurnLeft(const FInputActionValue& Value) {
	UE_LOG(LogTemp, Display, TEXT("Left"));
	movementComponent->Turn(StaticMeshComponent, -90);
}

void APrimaryObjectBase::TurnRight(const FInputActionValue& Value) {
	UE_LOG(LogTemp, Display, TEXT("Right"));
	movementComponent->Turn(StaticMeshComponent, 90);
}

void APrimaryObjectBase::Jump(const FInputActionValue& Value) {
	if (GroundCheck()) {
		StaticMeshComponent->AddImpulse(FVector(0, 0, 100000));
		UE_LOG(LogTemp, Display, TEXT("Jump"));
	}
}

void APrimaryObjectBase::BoostStart(const FInputActionValue& Value) {
	if (canDash && boostTimer > 0.08f) {
		movementComponent->movementSpeed = 80;
		boostTimer = 0;
		canDash = false;
	}
}

void APrimaryObjectBase::BoostEnd(const FInputActionValue& Value) {
	//movementComponent->movementSpeed = 10;
}

void APrimaryObjectBase::Toggle(const FInputActionValue& Value) {
	Paused = !Paused;
	PauseWidget->ResumeButton->SetUserFocus(PlayerController);
	PauseWidget->SwitchInput(SubSystem, InputSystemComponent);
	if (PauseWidget != nullptr) {
		PauseWidget->OnPause();
	}
}

void APrimaryObjectBase::PausedSelect(const FInputActionValue& Value) {
	FVector2D axis = Value.Get<FVector2D>();
	PauseWidget->OnSelect(axis.X, PlayerController);
}


bool APrimaryObjectBase::GroundCheck() {
	FVector startLocation = GetActorLocation();
	FVector endLocation = startLocation - FVector(0, 0, 100);

	ECollisionChannel collisionChannel = ECC_WorldStatic;

	FHitResult hitResult;
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, collisionChannel, queryParams)) {
		return true;
	}
	else {
		return false;
	}
}

void APrimaryObjectBase::MovePlayer(FVector fvector) {
	StaticMeshComponent->SetWorldLocation(fvector);
	CurrentPosition = fvector;
}

// Called when the game starts or when spawned
void APrimaryObjectBase::BeginPlay() {
	Super::BeginPlay();
	PlayerPosition1 = FVector(101.887642f, 2924.44733f, 39.887158f);
	PlayerPosition2 = FVector(-35.965259f, 2924.44733f, 39.887158f);
	PlayerPosition3 = FVector(-184.489698f, 2924.44733f, 39.887158f);
	PlayerPositions.Add(PlayerPosition1);
	PlayerPositions.Add(PlayerPosition2);
	PlayerPositions.Add(PlayerPosition3);
	PlayerPositionIndex = 1;
	MovePlayer(PlayerPositions[PlayerPositionIndex]);


	PauseWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass);
	UITextWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), UITextWidgetClass);
	UE_LOG(LogTemp, Display, TEXT("Widgetclass is %s"), *PauseWidgetClass->GetName());

	if (PauseWidgetInstance != nullptr) {
		PauseWidgetInstance->AddToViewport();
		UE_LOG(LogTemp, Display, TEXT("Widget is %s"), *PauseWidgetInstance->GetName());
		UE_LOG(LogTemp, Display, TEXT("Widget is not Null"));
		if (PauseWidgetInstance->IsInViewport()) {
			PauseWidget = CastChecked<UPauseMenuWidget>(PauseWidgetInstance);
			UE_LOG(LogTemp, Display, TEXT("Widget is in viewport"));
		}
		else {
			UE_LOG(LogTemp, Display, TEXT("Widget is not in viewport"));
		}
	}
	PauseWidget->CacheSubAndInput(SubSystem, InputSystemComponent);

	if (UITextWidgetInstance == nullptr) {
		UE_LOG(LogTemp, Display, TEXT("UITEXT is null"));
	}

	if (UITextWidgetInstance != nullptr) {
		UITextWidgetInstance->AddToViewport();
		UE_LOG(LogTemp, Display, TEXT("UITEXT is added to viewport"));
		if (UITextWidgetInstance->IsInViewport()) {
			UE_LOG(LogTemp, Display, TEXT("UITEXT is in viewport"));
			UITextWidget = CastChecked<UTextElementsWidget>(UITextWidgetInstance);
			UITextWidget->PlayAnimation(UITextWidget->TimeText, 0, 1);
			UITextWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}

}

// Called every frame
void APrimaryObjectBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	TimeFromStart += DeltaTime;

	if (TimeFromStart >= 2 && TimeFromStart <= 2.5f) {
		UITextWidget->ReadyText->SetText(FText::FromString(TEXT("Set..")));
	}
	if (TimeFromStart >= 3 && TimeFromStart <= 3.5f) {
		UITextWidget->ReadyText->SetText(FText::FromString(TEXT("GO!")));
		UITextWidget->PlayAnimation(UITextWidget->ReadyFade);
		GameStarted = true;
	}
	CameraComponent->LerpCamera(DeltaTime, StaticMeshComponent, CameraComponent->SpringArmComponent);
	if (GameStarted == true) {
		//movementComponent->Move(DeltaTime, StaticMeshComponent, moveInput);
		jumpTimer += DeltaTime;
		boostTimer += DeltaTime;
		TotalTime += DeltaTime;
		int Min = (int)(TotalTime / 60);
		int Sec = ((int)TotalTime % 60);
		int MSec = ((int)(TotalTime * 1000) % 1000);
		UITextWidget->SetTimer(MSec, Sec, Min);

		if (boostTimer > 0.08f) {
			movementComponent->movementSpeed = 10;
		}
		if (GroundCheck()) {
			canDash = true;
		}
	}
}
