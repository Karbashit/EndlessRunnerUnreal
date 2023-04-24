// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.h"
#include "PlatformFactory.generated.h"


UCLASS()
class TUTORIALPROJECT2_API APlatformFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformFactory();

	UPROPERTY(EditAnywhere, Category="GameConfig")
	TSubclassOf<AMovingPlatform> MovingPlatformClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void SpawnPlatforms();
	void RepositionPlatform(AMovingPlatform* platform1, AMovingPlatform* platform2);
	TArray<AMovingPlatform*> PlatformPool;
	

};
