// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingPlatform.h"
#include "GameFramework/Actor.h"
#include "PlatformObjectPool.generated.h"

UCLASS()
class TUTORIALPROJECT2_API APlatformObjectPool : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlatformObjectPool();

	AMovingPlatform* GetPooledPlatform();
	void ReleasePooledObject(AMovingPlatform Platform);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	TArray<AMovingPlatform*> PlatformPool;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Platform")
	TSubclassOf<AMovingPlatform> PlatformClass;
};
