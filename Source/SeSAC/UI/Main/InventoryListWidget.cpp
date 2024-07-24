// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryListWidget.h"

#include "ItemData.h"
#include "Components/ListView.h"
#include "InventoryListEntryWidget.h"

void UInventoryListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mTitleBar = Cast<UButton>(GetWidgetFromName(TEXT("TitleBar")));
	
	mCloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));
	mCloseButton->OnClicked.AddDynamic(this, &UInventoryListWidget::CloseButtonClick);

	mInventoryList = Cast<UListView>(GetWidgetFromName(TEXT("InventoryList")));
	
	mInventoryList->OnItemClicked().AddUObject(this, &UInventoryListWidget::ListItemClick);
	mInventoryList->OnItemIsHoveredChanged().AddUObject(this, &UInventoryListWidget::ListItemHovered);
	mInventoryList->OnItemSelectionChanged().AddUObject(this, &UInventoryListWidget::ListItemSelect);
	mInventoryList->OnItemDoubleClicked().AddUObject(this, &UInventoryListWidget::ListItemDoubleClick);
	

	for (int32 i = 0; i < 20; i++)
	{
		// FMath::RandRange(0,2);
		UItemData* Data = NewObject<UItemData>();
		Data->mItemName = FString::Printf(TEXT("Item %d"), i);
		Data->mItemCount = 10;
		Data->mIcon = LoadObject<UTexture2D>(GetWorld(), TEXT("/Game/UIAsset/Adventure/Tex_letter.Tex_letter"));

		mInventoryList->AddItem(Data);
	}
}

void UInventoryListWidget::CloseButtonClick()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UInventoryListWidget::ListItemClick(UObject* Item)
{
	UItemData* Data = Cast<UItemData>(Item);

	if (IsValid(Data))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Magenta, Data->mItemName);
	}
}

void UInventoryListWidget::ListItemHovered(UObject* Item, bool Hovered)
{
	UItemData* Data = Cast<UItemData>(Item);

	if (mSelectItem != Item)
	{
		Data->mOnMouse = Hovered;

		UInventoryListEntryWidget* EntryWidget = mInventoryList->GetEntryWidgetFromItem<UInventoryListEntryWidget>(Item);
		if (IsValid(EntryWidget))
		{
			if (Hovered)
			{
				EntryWidget->SetMouseState(EEntryWidgetMouseState::MouseOn);
			}
			else
			{
				EntryWidget->SetMouseState(EEntryWidgetMouseState::None);
			}
		}
	}
}

void UInventoryListWidget::ListItemSelect(UObject* Item)
{
	// 기존에 선택된 아이템이 있을 경우, 이 아이템은 None으로 만들어줌
	if (IsValid(mSelectItem))
	{
		mSelectItem->mSelect = false;

		UInventoryListEntryWidget* EntryWidget = mInventoryList->GetEntryWidgetFromItem<UInventoryListEntryWidget>(mSelectItem);
		if (IsValid(EntryWidget))
		{
			EntryWidget->SetMouseState(EEntryWidgetMouseState::None);
		}
	}

	mSelectItem = Cast<UItemData>(Item);
	
	// 새로 선택한 아이템을 선택 상태로 만들어줌
	if (IsValid(mSelectItem))
	{
		mSelectItem->mSelect = true;

		UInventoryListEntryWidget* EntryWidget = mInventoryList->GetEntryWidgetFromItem<UInventoryListEntryWidget>(mSelectItem);
		if (IsValid(EntryWidget))
		{
			EntryWidget->SetMouseState(EEntryWidgetMouseState::Select);
		}
	}
}

void UInventoryListWidget::ListItemDoubleClick(UObject* Item)
{
	// ListView의 모든 아이텡믈 다 지움
	// mInventoryList->ClearListItems();

	mInventoryList->RemoveItem(Item);
}
