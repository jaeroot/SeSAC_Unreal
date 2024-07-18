// Fill out your copyright notice in the Description page of Project Settings.


#include "InGamePlayerController.h"

#include "SeSAC/UI/Main/MainWidget.h"

AInGamePlayerController::AInGamePlayerController()
{
	static ConstructorHelpers::FClassFinder<UMainWidget>
		UIAsset(TEXT("/Game/UI/Main/WB_Main.WB_Main_C"));
	if(UIAsset.Succeeded())
	{
		mWidgetClass = UIAsset.Class;
	}

	bShowMouseCursor = true;
}

void AInGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(mWidgetClass))
	{
		mWidget = CreateWidget<UMainWidget>(GetWorld(), mWidgetClass);
		if (IsValid(mWidget))
		{
			mWidget->AddToViewport();
		}
	}

	FInputModeGameAndUI InputMode;
	SetInputMode(InputMode);
}

void AInGamePlayerController::SetPlayerName(const FString& Name)
{
	mWidget->SetPlayerName(Name);
}

void AInGamePlayerController::SetHPPercent(float Percent)
{
	mWidget->SetHPPercent(Percent);
}

void AInGamePlayerController::SetMPPercent(float Percent)
{
	mWidget->SetMPPercent(Percent);
}