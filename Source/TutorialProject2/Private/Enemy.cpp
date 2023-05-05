// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "CreateSharedUI.h"
#include "Kismet/GameplayStatics.h"
#include "TutorialProject2/PrimaryObjectBase.h"
#include "TutorialProject2/TutorialProject2GameModeBase.h"

// Sets default values
AEnemy::AEnemy() : LifeTime(0) {
	PrimaryActorTick.bCanEverTick = true;
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	RootComponent = TriggerVolume;
	TriggerVolume->SetCollisionProfileName("Trigger");

}


void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                            const FHitResult& SweepResult) {
	if (OtherActor->IsA(APrimaryObjectBase::StaticClass())) {
		APrimaryObjectBase* PrimaryObject = Cast<APrimaryObjectBase>(OtherActor);
		int32 HitPlayerIndex = PrimaryObject->PlayerIndex;

		ACreateSharedUI* SharedUI = Cast<ACreateSharedUI>(UGameplayStatics::GetActorOfClass(GetWorld(), ACreateSharedUI::StaticClass()));
		SharedUI->RemoveLife(HitPlayerIndex);
		this->Destroy();
	}
}

void AEnemy::BeginPlay() {
	Super::BeginPlay();
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
}

bool AEnemy::LifeTimeIsGreater(float LifeTime1, float LifeTime2) {

	return LifeTime1 > LifeTime2;
}

void AEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	MoveEnemy(this, DeltaTime);

	if (GetActorLocation().Y < 500) {
		if (GetActorLocation().X < 0) {
			ATutorialProject2GameModeBase* GameMode = Cast<ATutorialProject2GameModeBase>(UGameplayStatics::GetGameMode(this));
			GameMode->score+=1;
			int32 RandomNumber = FMath::RandRange(0, 1);
			TArray<AActor*> FoundActors;
			TArray<TObjectPtr<AEnemy>> FoundActorsSortedByTime;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), FoundActors);

			for (auto enemy : FoundActors) {
				if (enemy != this) {
					FoundActorsSortedByTime.Add(Cast<AEnemy>(enemy));
				}
			}
			Algo::SortBy(FoundActorsSortedByTime, &AEnemy::LifeTime);
			if (RandomNumber == 1) {
				if (FoundActorsSortedByTime.Num() > 0) {
					FoundActorsSortedByTime[0]->Destroy();
				}
			}
			this->Destroy();
		}
		else {


			int32 RandomNumber = FMath::RandRange(0, 1);
			TArray<AActor*> FoundActors;
			TArray<TObjectPtr<AEnemy>> FoundActorsSortedByTime;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), FoundActors);

			for (auto enemy : FoundActors) {
				if (enemy != this) {
					FoundActorsSortedByTime.Add(Cast<AEnemy>(enemy));
				}
			}
			Algo::SortBy(FoundActorsSortedByTime, &AEnemy::LifeTime);
			if (RandomNumber == 1) {
				if (FoundActorsSortedByTime.Num() > 0) {
					FoundActorsSortedByTime[0]->Destroy();
				}
			}


			this->Destroy();
		}
	}
}

void AEnemy::MoveEnemy(AActor* actor, float DeltaTime) {
	actor->AddActorLocalOffset(FVector(0, speed * DeltaTime, 0));
	LifeTime += DeltaTime;
}
