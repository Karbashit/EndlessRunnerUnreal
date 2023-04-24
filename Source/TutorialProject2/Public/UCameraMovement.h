// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "TutorialProject2/PrimaryObjectBase.h"
#include "UCameraMovement.generated.h"


class APrimaryObjectBase;

UCLASS()
class TUTORIALPROJECT2_API UCameraMovement : public USceneComponent {
	GENERATED_BODY()
public:
	UCameraMovement();
	~UCameraMovement();
	void LerpCamera(float DeltaTime, UStaticMeshComponent* object, USpringArmComponent* springarm);
	float InterpTime = 0.10f;

	UPROPERTY(EditAnywhere, Category="SpringArmCamera")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, Category="SpringArmCamera")
	UCameraComponent* CameraComponent;

private:
protected:
};
