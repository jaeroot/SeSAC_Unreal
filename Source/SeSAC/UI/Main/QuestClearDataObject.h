// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/UI/UIInfo.h"
#include "SeSAC/GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "QuestClearDataObject.generated.h"

/**
 * 
 */
UCLASS()
class SESAC_API UQuestClearDataObject : public UObject
{
	GENERATED_BODY()

	friend class UQuestWidget;
	friend class UQuestInfoWidget;
	friend class UQuestClearDataEntryWidget;
	
protected:
	FQuestClearUseData mClearData;
};
