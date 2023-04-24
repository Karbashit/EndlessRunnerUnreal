// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInput/Public/InputActionValue.h"
#include "UMovement.generated.h"

class APrimaryObjectBase;


UCLASS()
class TUTORIALPROJECT2_API UMovement : public USceneComponent
{
GENERATED_BODY()
public:
	UMovement();
	~UMovement();

	UPROPERTY(EditAnywhere, Category="MovementProperties")
	float movementSpeed = 10;

	void Move(float deltaTime, UStaticMeshComponent* objectBase, FVector2d Movement);
	void Turn(UStaticMeshComponent* objectBase, float Turn);
};
