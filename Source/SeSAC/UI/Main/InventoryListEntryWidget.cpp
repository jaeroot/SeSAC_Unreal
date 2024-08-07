// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryListEntryWidget.h"

#include "ItemData.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UInventoryListEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mIcon = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));
	mNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	mCountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CountText")));
	mSelect = Cast<UImage>(GetWidgetFromName(TEXT("Select")));
}

void UInventoryListEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UItemData* Data = Cast<UItemData>(ListItemObject);

	if (IsValid(Data))
	{
		mIcon->SetBrushFromTexture(Data->mIcon);
		mNameText->SetText(FText::FromString(Data->mItemName));
		mCountText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Data->mItemCount)));

		if (Data->mSelect)
		{
			SetMouseState(EEntryWidgetMouseState::Select);
		}
		else if (Data->mOnMouse)
		{
			SetMouseState(EEntryWidgetMouseState::MouseOn);
		}
		else
		{
			SetMouseState(EEntryWidgetMouseState::None);
		}
	}
}

void UInventoryListEntryWidget::SetMouseState(EEntryWidgetMouseState State)
{
	switch (State)
	{
	case EEntryWidgetMouseState::None:
		mSelect->SetVisibility(ESlateVisibility::Collapsed);
		mSelect->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
		break;
	case EEntryWidgetMouseState::MouseOn:
		mSelect->SetVisibility(ESlateVisibility::Visible);
		mSelect->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 0.0f, 0.3f));
		break;
	case EEntryWidgetMouseState::Select:
		mSelect->SetVisibility(ESlateVisibility::Visible);
		mSelect->SetColorAndOpacity(FLinearColor(1.0f, 0.0f, 0.0f, 0.3f));
		break;
	}
}
