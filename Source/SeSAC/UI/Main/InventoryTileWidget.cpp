// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryTileWidget.h"

#include "InventoryTileEntryWidget.h"
#include "ItemData.h"
#include "ItemInfoWidget.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/TileView.h"


void UInventoryTileWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mTitleBar = Cast<UButton>(GetWidgetFromName(TEXT("TitleBar")));
	
	mCloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));
	mCloseButton->OnClicked.AddDynamic(this, &UInventoryTileWidget::CloseButtonClick);

	mInventoryTile = Cast<UTileView>(GetWidgetFromName(TEXT("InventoryTile")));
	
	mInventoryTile->OnItemClicked().AddUObject(this, &UInventoryTileWidget::TileItemClick);
	mInventoryTile->OnItemIsHoveredChanged().AddUObject(this, &UInventoryTileWidget::TileItemHovered);
	mInventoryTile->OnItemSelectionChanged().AddUObject(this, &UInventoryTileWidget::TileItemSelect);
	mInventoryTile->OnItemDoubleClicked().AddUObject(this, &UInventoryTileWidget::TileItemDoubleClick);
	

	for (int32 i = 0; i < 20; i++)
	{
		// FMath::RandRange(0,2);
		UItemData* Data = NewObject<UItemData>();
		Data->mItemName = FString::Printf(TEXT("Item %d"), i);
		Data->mItemCount = i;
		Data->mIcon = LoadObject<UTexture2D>(GetWorld(), TEXT("/Game/UIAsset/Adventure/Tex_letter.Tex_letter"));

		mInventoryTile->AddItem(Data);
	}

	mItemInfo = Cast<UItemInfoWidget>(GetWidgetFromName(TEXT("WB_ItemInfo")));
}

FReply UInventoryTileWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseMove(InGeometry, InMouseEvent);

	if (IsValid(mHoveredItem))
	{
		UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(mItemInfo->Slot);

		if (IsValid(PanelSlot))
		{
			// Screen 공간의 마우스 위치를 얻어옴. Screen 좌표값임
			FVector2D MousePos = InMouseEvent.GetScreenSpacePosition();

			// Screen에서의 값을 Widget에서의 위치로 변경
			FVector2D WidgetPos = USlateBlueprintLibrary::AbsoluteToLocal(InGeometry, MousePos);

			PanelSlot->SetPosition(WidgetPos);
		}
	}
	
	return result;
}

void UInventoryTileWidget::CloseButtonClick()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UInventoryTileWidget::TileItemClick(UObject* Item)
{
	UItemData* Data = Cast<UItemData>(Item);

	if (IsValid(Data))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Magenta, Data->mItemName);
	}
}

void UInventoryTileWidget::TileItemHovered(UObject* Item, bool Hovered)
{
	UItemData* Data = Cast<UItemData>(Item);

	if (mSelectItem != Item)
	{
		Data->mOnMouse = Hovered;

		UInventoryTileEntryWidget* EntryWidget = mInventoryTile->GetEntryWidgetFromItem<UInventoryTileEntryWidget>(Item);
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

	if (Hovered)
	{
		mHoveredItem = Data;
		
		mItemInfo->SetVisibility(ESlateVisibility::HitTestInvisible);
		
		mItemInfo->mIcon->SetBrushFromTexture(mHoveredItem->mIcon);
		mItemInfo->mItemName->SetText(FText::FromString(mHoveredItem->mItemName));
		mItemInfo->mItemContent->SetText(FText::FromString(mHoveredItem->mItemName));
	}
	else
	{
		if (IsValid(mHoveredItem))
		{
			mItemInfo->SetVisibility(ESlateVisibility::Collapsed);
		}
		
		mHoveredItem = nullptr;
	}
}

void UInventoryTileWidget::TileItemSelect(UObject* Item)
{
	// 기존에 선택된 아이템이 있을 경우, 이 아이템은 None으로 만들어줌
	if (IsValid(mSelectItem))
	{
		mSelectItem->mSelect = false;

		UInventoryTileEntryWidget* EntryWidget = mInventoryTile->GetEntryWidgetFromItem<UInventoryTileEntryWidget>(mSelectItem);
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

		UInventoryTileEntryWidget* EntryWidget = mInventoryTile->GetEntryWidgetFromItem<UInventoryTileEntryWidget>(mSelectItem);
		if (IsValid(EntryWidget))
		{
			EntryWidget->SetMouseState(EEntryWidgetMouseState::Select);
		}
	}
}

void UInventoryTileWidget::TileItemDoubleClick(UObject* Item)
{
	// ListView의 모든 아이텡믈 다 지움
	// mInventoryTile->ClearListItems();

	mInventoryTile->RemoveItem(Item);
}
