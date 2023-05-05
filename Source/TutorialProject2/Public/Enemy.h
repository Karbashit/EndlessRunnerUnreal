// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreateSharedUI.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class TUTORIALPROJECT2_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();
	

	
	int speed;
	UBoxComponent* TriggerVolume;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	float LifeTime;

	int32 Lane;

	bool LifeTimeIsGreater(float LifeTime1, float LifeTime2);
	
	
	virtual void Tick(float DeltaTime) override;
	void MoveEnemy(AActor* actor, float DeltaTime);

};
