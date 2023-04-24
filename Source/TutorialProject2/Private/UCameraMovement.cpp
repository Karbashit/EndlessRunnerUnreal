// Fill out your copyright notice in the Description page of Project Settings.

#include "UCameraMovement.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "TutorialProject2/PrimaryObjectBase.h"

UCameraMovement::UCameraMovement()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetRelativeLocation(FVector(0, 0, 70));
	SpringArmComponent->TargetArmLength = 400;
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	FVector cameraLocRelativeToSpring = FVector(-400, 0, 140);
	FRotator cameraRotation = FRotator(-10, 0, 0);
	CameraComponent->SetRelativeLocation(cameraLocRelativeToSpring);
	CameraComponent->SetRelativeRotation(cameraRotation);
	CameraComponent->bUsePawnControlRotation = false;
}

UCameraMovement::~UCameraMovement()
{
}

void UCameraMovement::LerpCamera(float DeltaTime, UStaticMeshComponent* object, USpringArmComponent* springarm) {
	FRotator currentRot = springarm->GetRelativeTransform().GetRotation().Rotator();
	FRotator targetRot = object->GetRelativeTransform().GetRotation().Rotator();

	float InterpPercentage = FMath::Clamp<float>(DeltaTime / InterpTime, 0.f, 1.f);
	
	FRotator NewRotation = FMath::Lerp(currentRot, targetRot, InterpPercentage);
	
	springarm->SetRelativeRotation(NewRotation);
}
