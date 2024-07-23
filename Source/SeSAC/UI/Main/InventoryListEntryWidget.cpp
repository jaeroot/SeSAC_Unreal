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
}

void UInventoryListEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UItemData* Data = Cast<UItemData>(ListItemObject);

	if (IsValid(Data))
	{
		mIcon->SetBrushFromTexture(Data->mIcon);
		mNameText->SetText(FText::FromString(Data->mItemName));
		mCountText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Data->mItemCount)));
	}
}
