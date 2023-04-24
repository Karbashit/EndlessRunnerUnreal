// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	SetRootComponent(RootComponent);
	Arrow->SetupAttachment(RootComponent);
}

void AMovingPlatform::SetInUse(bool boolen)
{
	IsInUse = boolen;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlatform(this, DeltaTime);
}

void AMovingPlatform::MovePlatform(AActor* actor, float DeltaTime)
{
	actor->AddActorLocalOffset(FVector(0, -700*DeltaTime, 0));
}


