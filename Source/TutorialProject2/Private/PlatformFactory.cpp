// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformFactory.h"
#include "Engine/World.h"
#include "MemPro/MemPro.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Actor.h"


// Sets default values
APlatformFactory::APlatformFactory()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APlatformFactory::BeginPlay()
{
	Super::BeginPlay();
	SpawnPlatforms();
}

// Called every frame
void APlatformFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector FrontPlatformPosition = PlatformPool[0]->GetActorLocation();
	if (FrontPlatformPosition.Y < 0)
	{
		RepositionPlatform(PlatformPool[0], PlatformPool.Top());
	}
}

void APlatformFactory::SpawnPlatforms()
{
	FVector Offset(0, 100, 0);
	for (int i = 0; i <= 10; i++)
	{
		if (PlatformPool.IsEmpty())
		{
			AMovingPlatform* NewPlatform = GetWorld()->SpawnActor<AMovingPlatform>(MovingPlatformClass, FVector::Zero(),
			                                                      FRotator::ZeroRotator);
			PlatformPool.Add(NewPlatform);
		}
		else
		{
			FVector SpawnLocation = PlatformPool[i - 1]->Arrow->GetComponentLocation() +
				Offset * i;
			AMovingPlatform* NewPlatform = GetWorld()->SpawnActor<AMovingPlatform>(MovingPlatformClass,
			                                                      SpawnLocation, FRotator::ZeroRotator);
			NewPlatform->SetActorLocation(SpawnLocation);
			PlatformPool.Add(NewPlatform);
		}
	}
}

void APlatformFactory::RepositionPlatform(AMovingPlatform* platform1, AMovingPlatform* platform2)
{
	FVector Offset(0, 1175, 0);
	FVector Platform2Position = platform2->GetActorLocation();
	platform1->SetActorLocation(Platform2Position + Offset);
	AMovingPlatform* CachedPlatform = platform1;
	PlatformPool.Add(CachedPlatform);
	PlatformPool.RemoveAt(0);
}
