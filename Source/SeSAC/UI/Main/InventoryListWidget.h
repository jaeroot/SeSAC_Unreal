// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/UI/UIInfo.h"
#include "SeSAC/GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "InventoryListWidget.generated.h"

class UItemData;
class UListView;
/**
 * 
 */
UCLASS()
class SESAC_API UInventoryListWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION()
	void CloseButtonClick();

	UFUNCTION()
	void ListItemClick(UObject* Item);

	UFUNCTION()
	void ListItemHovered(UObject* Item, bool Hovered);

	UFUNCTION()
	void ListItemSelect(UObject* Item);

	UFUNCTION()
	void ListItemDoubleClick(UObject* Item);

protected:
	UButton* mTitleBar;
	UButton* mCloseButton;
	UListView* mInventoryList;

	UItemData* mSelectItem = nullptr;
};
