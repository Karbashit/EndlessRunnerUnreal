// Copyright Epic Games, Inc. All Rights Reserved.


#include "TutorialProject2GameModeBase.h"
#include "Kismet/GameplayStatics.h"

ATutorialProject2GameModeBase::ATutorialProject2GameModeBase() {

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player1Obj"));
	if (PlayerPawnBPClass.Class != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("is found"));
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("is not found"));
	}

	UE_LOG(LogTemp, Warning, TEXT("Character = %s"), *PlayerPawnBPClass.GetReferencerName());

}

void ATutorialProject2GameModeBase::BeginPlay() {
	UGameplayStatics::CreatePlayer(GetWorld(), 1, true);
	Super::BeginPlay();
}
