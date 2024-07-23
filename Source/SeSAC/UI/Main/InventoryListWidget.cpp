// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryListWidget.h"

#include "ItemData.h"
#include "Components/ListView.h"

void UInventoryListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mTitleBar = Cast<UButton>(GetWidgetFromName(TEXT("TitleBar")));
	
	mCloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));
	mCloseButton->OnClicked.AddDynamic(this, &UInventoryListWidget::CloseButtonClick);

	mInventoryList = Cast<UListView>(GetWidgetFromName(TEXT("InventoryList")));
	
	mInventoryList->OnItemClicked().AddUObject(this, &UInventoryListWidget::ListItemClick);
	// mInventoryList->OnItemDoubleClicked().AddUObject();
	mInventoryList->OnItemIsHoveredChanged().AddUObject(this, &UInventoryListWidget::ListItemHovered);
	

	for (int32 i = 0; i < 20; i++)
	{
		UItemData* Data = NewObject<UItemData>();
		Data->mItemName = TEXT("Item");
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
	
}
