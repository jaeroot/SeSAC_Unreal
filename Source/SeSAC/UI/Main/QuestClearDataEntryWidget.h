// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/IUserObjectListEntry.h"
#include "SeSAC/UI/UIInfo.h"
#include "SeSAC/GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "QuestClearDataEntryWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class SESAC_API UQuestClearDataEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

protected:
	UTextBlock* mNameText;
	UTextBlock* mCountText;
};
