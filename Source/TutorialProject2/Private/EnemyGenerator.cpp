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
	
	if(SpawnLocation.X > 0) {
		NewEnemy->Lane = 0;
	}
	else {
		NewEnemy->Lane = 1;
	}
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

