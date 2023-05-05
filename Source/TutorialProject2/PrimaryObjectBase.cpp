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
#include "Kismet/GameplayStatics.h"
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
	//CameraComponent = CreateDefaultSubobject<UCameraMovement>("CameraMovement");
	movementComponent = CreateDefaultSubobject<UMovement>("UMovement");
	InputSystemComponent = CreateDefaultSubobject<UInputSystem>("UInputSystem");

	APrimaryObjectBase::SetupPlayerInputComponent(InputSystemComponent);
	StaticMeshComponent->SetSimulatePhysics(true);
	SetRootComponent(StaticMeshComponent);
	// CameraComponent->SpringArmComponent->AttachToComponent(GetRootComponent(),
	//                                                        FAttachmentTransformRules::KeepRelativeTransform);
	// CameraComponent->CameraComponent->AttachToComponent(CameraComponent->SpringArmComponent,
	//                                                     FAttachmentTransformRules::KeepRelativeTransform)
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
		PEI->BindAction(InputSystemComponent->InputMoveLeftP2, ETriggerEvent::Triggered, this,
		                &APrimaryObjectBase::MoveLeftP2);
		PEI->BindAction(InputSystemComponent->InputMoveRightP2, ETriggerEvent::Triggered, this,
		                &APrimaryObjectBase::MoveRightP2);
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
		MovePlayer(GetCorrectArray(PlayerIndex)[PlayerPositionIndex]); 
	}
	else {
		return;
	}
}

void APrimaryObjectBase::MoveRight(const FInputActionValue& Value) {
	if (PlayerPositionIndex < 2) {
		PlayerPositionIndex++;
		MovePlayer(GetCorrectArray(PlayerIndex)[PlayerPositionIndex]); 
	}
	else {
		return;
	}
}


void APrimaryObjectBase::MoveLeftP2(const FInputActionValue& Value) {
	APrimaryObjectBase* TempBase = Cast<APrimaryObjectBase>(
		UGameplayStatics::GetPlayerController(GetWorld(), 1)->GetCharacter());
	if (TempBase) {
		TempBase->MoveLeft(Value);
	}
}

void APrimaryObjectBase::MoveRightP2(const FInputActionValue& Value) {
	APrimaryObjectBase* TempBase = Cast<APrimaryObjectBase>(
		UGameplayStatics::GetPlayerController(GetWorld(), 1)->GetCharacter());
	if (TempBase) {
		TempBase->MoveRight(Value);
	}
}

void APrimaryObjectBase::RemoveLife() {

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

TArray<FVector> APrimaryObjectBase::GetCorrectArray(int playerNumbner) {
	if (playerNumbner == 0) {
		return Player1Positions;
	}
	return Player2Positions;
}

// Called when the game starts or when spawned
void APrimaryObjectBase::BeginPlay() {
	Super::BeginPlay();

	PlayerPositionIndex = 1;


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
	// PauseWidget->CacheSubAndInput(SubSystem, InputSystemComponent);

	if (this->GetName() == "Player1Obj_C_0") {
		SetActorLocation(FVector(442.743762f, 3492.18148f, 65.576674f));
		Player1Positions.Add(Player1Position1);
		Player1Positions.Add(Player1Position2);
		Player1Positions.Add(Player1Position3);
	}
	else {
		SetActorLocation(FVector(-519.085065f, 3492.18148f, 65.576674f));
		Player2Positions.Add(Player2Position1);
		Player2Positions.Add(Player2Position2);
		Player2Positions.Add(Player2Position3);
	}


	if (GetActorLocation().X > 0) {
		PlayerIndex = 0;
	}
	else {
		PlayerIndex = 1;
	}

}

// Called every frame
void APrimaryObjectBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);


	// CameraComponent->LerpCamera(DeltaTime, StaticMeshComponent, CameraComponent->SpringArmComponent);
	//movementComponent->Move(DeltaTime, StaticMeshComponent, moveInput);
	jumpTimer += DeltaTime;
	boostTimer += DeltaTime;


	if (boostTimer > 0.08f) {
		movementComponent->movementSpeed = 10;
	}
	if (GroundCheck()) {
		canDash = true;
	}
}
