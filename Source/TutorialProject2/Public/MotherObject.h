// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutorialProject2/PrimaryObjectBase.h"
#include "MotherObject.generated.h"

UCLASS()
class TUTORIALPROJECT2_API AMotherObject : public AActor
{
	GENERATED_BODY()

public:
	AMotherObject();
	
	UPROPERTY(EditAnywhere, Category="PlayerTwo")
	TSubclassOf<APrimaryObjectBase> PlayerClass;

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
