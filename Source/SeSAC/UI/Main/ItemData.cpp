// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemData.h"

UItemData::UItemData()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>
		ItemInfoTable(TEXT("/Game/UI/Main/DT_ItemInfo.DT_ItemInfo"));
	
	if (ItemInfoTable.Succeeded())
	{
		mItemInfoTable = ItemInfoTable.Object;
	}
}
