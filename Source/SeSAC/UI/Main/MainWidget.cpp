// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"

#include "PlayerHUDWidget.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mPlayerHUD = Cast<UPlayerHUDWidget>(GetWidgetFromName(TEXT("WB_PlayerHUD")));
	UE_LOG(LogTemp, Warning, TEXT("MainWidget NativeConstruct"));
}

void UMainWidget::SetPlayerName(const FString& Name)
{
	mPlayerHUD->SetPlayerName(Name);
}

void UMainWidget::SetHPPercent(float Percent)
{
	mPlayerHUD->SetHPPercent(Percent);
}

void UMainWidget::SetMPPercent(float Percent)
{
	mPlayerHUD->SetMPPercent(Percent);
}
