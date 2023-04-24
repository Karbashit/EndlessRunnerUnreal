// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformObjectPool.h"

#include <pplwin.h>

// Sets default values
APlatformObjectPool::APlatformObjectPool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlatformPool.Init(CreateDefaultSubobject<AMovingPlatform>("MovingPlatform"), 0);
}

// AMovingPlatform* APlatformObjectPool::GetPooledPlatform()
// {
// 	AMovingPlatform* PlatformToAdd = PlatformClass;
// 	return PlatformToAdd;
// 	// for (AMovingPlatform* Platform : PlatformPool)
// 	// {
// 	// 	if(!Platform->IsInUse)
// 	// 	{
// 	// 		Platform->SetInUse(true);
// 	// 		Platform->Reset();
// 	// 		return Platform;
// 	// 	}
// 	// }
// 	// return nullptr;
// }

// void APlatformObjectPool::ReleasePooledObject(AMovingPlatform* Platform)
// {
// 	Platform->SetInUse(false);
// 	AMovingPlatform* ElementToMove = PlatformPool[0];
// 	PlatformPool.Remove(ElementToMove);
// 	PlatformPool.Add(ElementToMove);
// }


// Called when the game starts or when spawned
void APlatformObjectPool::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlatformObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
