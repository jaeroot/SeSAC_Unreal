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
	
public:
	UItemData();

private:
	FString mItemName;
	FString mItemContent;
	int32 mItemCount = 0;
	UTexture2D* mIcon = nullptr;
	bool mOnMouse = false;
	bool mSelect = false;

private:
	UDataTable* mItemInfoTable = nullptr;
	
};

USTRUCT()
struct FItemInfoTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ItemContent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Icon;
};
