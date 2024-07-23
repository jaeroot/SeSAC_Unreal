// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterHeadInfoWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "SeSAC/Player/SeSACPlayerState.h"

void UCharacterHeadInfoWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	mPlayerName = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	mHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
}

void UCharacterHeadInfoWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UCharacterHeadInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//
	// ASeSACPlayerState* State = GetOwningPlayerState<ASeSACPlayerState>();
	// if (IsValid(State))
	// {
	// 	State->AddHPDelegate<UCharacterHeadInfoWidget>(this, &UCharacterHeadInfoWidget::SetHPPercent);
	// }
}

void UCharacterHeadInfoWidget::SetPlayerName(const FString& Name)
{
	mPlayerName->SetText(FText::FromString(Name));
}

void UCharacterHeadInfoWidget::SetHPPercent(float Percent)
{
	mHPBar->SetPercent(Percent);
}
