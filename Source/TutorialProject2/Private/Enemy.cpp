// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "TutorialProject2/PrimaryObjectBase.h"

// Sets default values
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	RootComponent = TriggerVolume;
	TriggerVolume->SetCollisionProfileName("Trigger");

}


void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if(OtherActor->IsA(APrimaryObjectBase::StaticClass())) {
		APrimaryObjectBase* PrimaryObject = Cast<APrimaryObjectBase>(OtherActor);
		PrimaryObject->UITextWidget->RemoveLife();
	}
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveEnemy(this, DeltaTime);

	if(GetActorLocation().Y < 500) {
		Destroy();
	}

}

void AEnemy::MoveEnemy(AActor* actor, float DeltaTime)
{
	actor->AddActorLocalOffset(FVector(0, speed*DeltaTime, 0));
}

