// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/UI/UIInfo.h"
#include "SeSAC/GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "ItemData.generated.h"

/**
 * 
 */
UCLASS()
class SESAC_API UItemData : public UObject
{
	GENERATED_BODY()

	friend class UInventoryListWidget;
	friend class UInventoryListEntryWidget;
	
	friend class UInventoryTileWidget;
	friend class UInventoryTileEntryWidget;

private:
	FString mItemName;
	int32 mItemCount;
	UTexture2D* mIcon;
	bool mOnMouse = false;
	bool mSelect = false;
	
};
