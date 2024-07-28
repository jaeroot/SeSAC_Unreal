// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestData.h"

UQuestData::UQuestData()
{
}

UQuestData* UQuestData::CreateChild(FQuestInfo* Info)
{
	UQuestData* Child = NewObject<UQuestData>();

	Child->mData.QuestType = Info->QuestType;
	Child->mData.Name = Info->Name;
	Child->mData.Content = Info->Content;
	Child->mData.Level = Info->Level;
	Child->mData.QuestEnable = true;
	Child->mTreeLevel = mTreeLevel + 1;

	for (FQuestClearData& Data : Info->ClearArray)
	{
		FQuestClearUseData ClearInfo;

		ClearInfo.Type = Data.Type;
		ClearInfo.ClearName = Data.ClearName;
		ClearInfo.ClearCount = 0;
		ClearInfo.ClearCountMax = Data.ClearCount;
		
		Child->mData.ClearArray.Add(ClearInfo);
	}

	mChildArray.Add(Child);

	return Child;
}
