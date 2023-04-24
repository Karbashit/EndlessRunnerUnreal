// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class TUTORIALPROJECT2_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();
	bool IsInUse;
	void SetInUse(bool boolen);
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Arrow")
	UArrowComponent* Arrow;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	void MovePlatform(AActor* actor, float DeltaTime);
	
};
