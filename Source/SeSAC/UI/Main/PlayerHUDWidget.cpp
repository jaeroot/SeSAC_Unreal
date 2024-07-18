// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"

#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mImage = Cast<UImage>(GetWidgetFromName(TEXT("PlayerImage")));
	mPlayerName = Cast<UTextBlock>(GetWidgetFromName(TEXT("PlayerName")));
	mHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	mMPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MPBar"))); 
}

void UPlayerHUDWidget::SetPlayerName(const FString& Name)
{
	mPlayerName->SetText(FText::FromString(Name));
}

void UPlayerHUDWidget::SetHPPercent(float Percent)
{
	mHPBar->SetPercent(Percent);
}

void UPlayerHUDWidget::SetMPPercent(float Percent)
{
	mMPBar->SetPercent(Percent);
}
