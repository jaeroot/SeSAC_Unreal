// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryTileEntryWidget.h"

#include "ItemData.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UInventoryTileEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mIcon = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));
	mCountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Count")));
	mSelect = Cast<UImage>(GetWidgetFromName(TEXT("Select")));
}

void UInventoryTileEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UItemData* Data = Cast<UItemData>(ListItemObject);

	if (IsValid(Data))
	{
		mIcon->SetBrushFromTexture(Data->mIcon);
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

void UInventoryTileEntryWidget::SetMouseState(EEntryWidgetMouseState State)
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
