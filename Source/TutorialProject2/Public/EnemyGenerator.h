// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "EnemyGenerator.generated.h"

UCLASS()
class TUTORIALPROJECT2_API AEnemyGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyGenerator();

	UPROPERTY(EditAnywhere, Category="EnemyClass")
	TSubclassOf<AEnemy> EnemyClass;

	FTimerHandle TimerHandle;

	void SpawnEnemy();


	FVector SpawnPosition1;
	FVector SpawnPosition2;
	FVector SpawnPosition3;
	TArray<FVector> SpawnPositions;
	int SpawnPositionIndex;

	int EnemySpeed = -700;

	float EnemySpawnInterval = 1;

	float TimeToIncreaseDifficulty;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
