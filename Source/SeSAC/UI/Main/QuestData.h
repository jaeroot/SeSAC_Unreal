// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/UI/UIInfo.h"
#include "SeSAC/GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "QuestData.generated.h"

/**
 * 
 */
UCLASS()
class SESAC_API UQuestData : public UObject
{
	GENERATED_BODY()

	friend class UQuestWidget;
	friend class UQuestEntryWidget;
	friend class UQuestInfoWidget;

public:
	UQuestData();

public:
	UQuestData* CreateChild(FQuestInfo* Info);
	
protected:
	FQuestInfoData mData;
	int32 mTreeLevel = 0;
	TArray<UObject*> mChildArray;
	bool mOnMouse = false;
	bool mSelect = false;
};
