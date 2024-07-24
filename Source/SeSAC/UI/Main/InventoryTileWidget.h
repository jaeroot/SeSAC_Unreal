// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/UI/UIInfo.h"
#include "SeSAC/GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "InventoryTileWidget.generated.h"

class UItemInfoWidget;
class UItemData;
class UTileView;
/**
 * 
 */
UCLASS()
class SESAC_API UInventoryTileWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

protected:
	UFUNCTION()
	void CloseButtonClick();

	UFUNCTION()
	void TileItemClick(UObject* Item);

	UFUNCTION()
	void TileItemHovered(UObject* Item, bool Hovered);

	UFUNCTION()
	void TileItemSelect(UObject* Item);

	UFUNCTION()
	void TileItemDoubleClick(UObject* Item);

protected:
	UButton* mTitleBar;
	UButton* mCloseButton;
	UTileView* mInventoryTile;

	UItemData* mSelectItem = nullptr;
	UItemData* mHoveredItem = nullptr;

	UItemInfoWidget* mItemInfo;
};
