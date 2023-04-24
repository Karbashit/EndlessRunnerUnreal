// Fill out your copyright notice in the Description page of Project Settings.

#include "TutorialProject2/Public/UMovement.h"
#include "TutorialProject2/PrimaryObjectBase.h"

UMovement::UMovement() {
}

UMovement::~UMovement() {
}

void UMovement::Move(float deltaTime, UStaticMeshComponent* objectBase, FVector2d Movement) {
	FVector currentVelocity = objectBase->GetPhysicsLinearVelocity();
	FVector rightVelocity = objectBase->GetRightVector() * Movement.X * movementSpeed * 100;

	//FVector forwardVelocity = objectBase->GetForwardVector() * movementSpeed * 100;
	//FVector desiredVelocity = forwardVelocity + rightVelocity + FVector(0, 0, currentVelocity.Z);

	objectBase->SetPhysicsLinearVelocity(rightVelocity, false);
}

void UMovement::Turn(UStaticMeshComponent* objectBase, float Turn) {
	objectBase->AddRelativeRotation(FRotator(0, Turn, 0));
}


