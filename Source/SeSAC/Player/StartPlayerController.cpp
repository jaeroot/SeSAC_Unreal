// Fill out your copyright notice in the Description page of Project Settings.


#include "StartPlayerController.h"

#include "SeSAC/UI/Start/StartWidget.h"

AStartPlayerController::AStartPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>
		UIAsset(TEXT("/Game/UI/Start/WB_Start.WB_Start_C"));
	if (UIAsset.Succeeded())
	{
		mWidgetClass = UIAsset.Class;
	}

	bShowMouseCursor = true;
}

void AStartPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(mWidgetClass))
	{
		mWidget = CreateWidget<UStartWidget>(GetWorld(), mWidgetClass);
		if (IsValid(mWidget))
		{
			mWidget->AddToViewport();
		}
	}

	FInputModeUIOnly InputMode;
	SetInputMode(InputMode);
}
