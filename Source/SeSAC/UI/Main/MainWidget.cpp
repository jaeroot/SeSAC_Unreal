// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"

#include "InventoryListWidget.h"
#include "PlayerHUDWidget.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mPlayerHUD = Cast<UPlayerHUDWidget>(GetWidgetFromName(TEXT("WB_PlayerHUD")));
	mInventory = Cast<UInventoryListWidget>(GetWidgetFromName(TEXT("WB_InventoryList")));
	
	mCharacterStateButton = Cast<UButton>(GetWidgetFromName(TEXT("CharacterStateButton")));
	mCharacterStateButton->OnClicked.AddDynamic(this, &UMainWidget::CharacterStateButtonClick);
	
	mInventoryButton = Cast<UButton>(GetWidgetFromName(TEXT("InventoryButton")));
	mInventoryButton->OnClicked.AddDynamic(this, &UMainWidget::InventoryButtonClick);
	
	mSkillButton = Cast<UButton>(GetWidgetFromName(TEXT("SkillButton")));
	mSkillButton->OnClicked.AddDynamic(this, &UMainWidget::SkillButtonClick);
	
	mOptionButton = Cast<UButton>(GetWidgetFromName(TEXT("OptionButton")));
	mOptionButton->OnClicked.AddDynamic(this, &UMainWidget::OptionButtonClick);
	
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

void UMainWidget::CharacterStateButtonClick()
{
}

void UMainWidget::InventoryButtonClick()
{
	if (mInventory->GetVisibility() == ESlateVisibility::Collapsed)
	{
		mInventory->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		mInventory->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMainWidget::SkillButtonClick()
{
}

void UMainWidget::OptionButtonClick()
{
}
