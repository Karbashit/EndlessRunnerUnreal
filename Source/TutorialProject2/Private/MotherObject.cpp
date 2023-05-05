// Fill out your copyright notice in the Description page of Project Settings.


#include "MotherObject.h"

// Sets default values
AMotherObject::AMotherObject()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMotherObject::BeginPlay()
{
	Super::BeginPlay();
	// APrimaryObjectBase* Player1 = GetWorld()->SpawnActor<APrimaryObjectBase>(PlayerClass, FVector::Zero(),
	// 														  FRotator::ZeroRotator);
	//
	// Player1->PlayerPosition1 = FVector(602.515941f, 2924.44733f, 39.887158f);
	// Player1->PlayerPosition2 = FVector(451.748436f, 2924.44733f, 39.887158f);
	// Player1->PlayerPosition3 = FVector(305.315444f, 2924.44733f, 39.887158f);
	//
	// APrimaryObjectBase* Player2 = GetWorld()->SpawnActor<APrimaryObjectBase>(PlayerClass, FVector::Zero(),
	// 													  FRotator::ZeroRotator);
	//
	// Player2->PlayerPosition1 = FVector(-656.938786f, 2924.44733f, 39.887158f);
	// Player2->PlayerPosition2 = FVector(-504.995539f, 2924.44733f, 39.887158f);
	// Player2->PlayerPosition3 = FVector(-352.402516f, 2924.44733f, 39.887158f);
}

// Called every frame
void AMotherObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

