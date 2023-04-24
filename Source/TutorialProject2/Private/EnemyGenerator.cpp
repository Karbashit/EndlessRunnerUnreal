// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyGenerator.h"
#include "TimerManager.h"

// Sets default values
AEnemyGenerator::AEnemyGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void AEnemyGenerator::BeginPlay()
{
	Super::BeginPlay();
	SpawnPosition1 = FVector(101.887642f, 13272.998087f, 64.317042f);
	SpawnPosition2 = FVector(-35.965259f, 13272.998087f, 64.317042f);
	SpawnPosition3 = FVector(-184.489698f, 13272.998087f, 64.317042f);
	SpawnPositions.Add(SpawnPosition1);
	SpawnPositions.Add(SpawnPosition2); 
	SpawnPositions.Add(SpawnPosition3);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyGenerator::SpawnEnemy, 2, true);
}

void AEnemyGenerator::SpawnEnemy() {
	SpawnPositionIndex = FMath::RandRange(0, 2);
	FVector SpawnLocation = SpawnPositions[SpawnPositionIndex];
	AEnemy* NewEnemy = GetWorld()->SpawnActor<AEnemy>(EnemyClass, SpawnLocation, FRotator::ZeroRotator);
	NewEnemy->speed = EnemySpeed;
}

// Called every frame
void AEnemyGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimeToIncreaseDifficulty+=DeltaTime;

	if(TimeToIncreaseDifficulty >= 15) {
		EnemySpeed-=300;
		FTimerHandle AnotherHandle;
		GetWorldTimerManager().SetTimer(AnotherHandle, this, &AEnemyGenerator::SpawnEnemy, 1, true);
		TimeToIncreaseDifficulty = 0;
	}

}

