// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateSharedUI.h"
#include "MenuHandler.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ACreateSharedUI::ACreateSharedUI() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACreateSharedUI::RemoveLife(int32 PlayerIndex) {
	AMenuHandler* MenuUI = Cast<AMenuHandler>(UGameplayStatics::GetActorOfClass(GetWorld(), AMenuHandler::StaticClass()));
	if (PlayerIndex == 0) {
		switch (Player1Life) {
		case 3:
			UITextWidget->Player1Life3->SetOpacity(0.0f);
			break;
		case 2:
			UITextWidget->Player1Life2->SetOpacity(0.0f);
			break;
		case 1:
			UITextWidget->Player1Life1->SetOpacity(0.0f);
			MenuUI->PlayerDead();
			break;
		default:
			break;
		}
		Player1Life -= 1;
	}
	else {
		switch (Player2Life) {
		case 3:
			UITextWidget->Player2Life1->SetOpacity(0.0f);
			break;
		case 2:
			UITextWidget->Player2Life2->SetOpacity(0.0f);
			break;
		case 1:
			UITextWidget->Player2Life3->SetOpacity(0.0f);
			MenuUI->PlayerDead();
			break;
		default:
			break;
		}
		Player2Life -= 1;
	}
}

// Called when the game starts or when spawned
void ACreateSharedUI::BeginPlay() {
	Super::BeginPlay();
	UITextWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), UITextWidgetClass);
	if (UITextWidgetInstance != nullptr) {
		UITextWidgetInstance->AddToViewport();
		UE_LOG(LogTemp, Display, TEXT("UITEXT is added to viewport"));
		if (UITextWidgetInstance->IsInViewport()) {
			UE_LOG(LogTemp, Display, TEXT("UITEXT is in viewport"));
			UITextWidget = CastChecked<UTextElementsWidget>(UITextWidgetInstance);
			UITextWidget->PlayAnimation(UITextWidget->TimeText, 0, 1);
			UITextWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}

}

// Called every frame
void ACreateSharedUI::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	TimeFromStart += DeltaTime;
	if (TimeFromStart >= 2 && TimeFromStart <= 2.5f) {
		if (UITextWidget) {
			UITextWidget->ReadyText->SetText(FText::FromString(TEXT("Set..")));
		}
	}
	if (TimeFromStart >= 3 && TimeFromStart <= 3.5f) {
		if (UITextWidget) {
			UITextWidget->ReadyText->SetText(FText::FromString(TEXT("GO!")));
			UITextWidget->PlayAnimation(UITextWidget->ReadyFade);
		}
		GameStarted = true;
	}

	if (GameStarted) {
		TotalTime += DeltaTime;
		int Min = (int)(TotalTime / 60);
		int Sec = ((int)TotalTime % 60);
		int MSec = ((int)(TotalTime * 1000) % 1000);
		if (UITextWidget) {
			UITextWidget->SetTimer(MSec, Sec, Min);
		}

	}

}
