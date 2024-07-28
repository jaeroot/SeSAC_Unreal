// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/IUserObjectListEntry.h"
#include "SeSAC/UI/UIInfo.h"
#include "SeSAC/GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "QuestEntryWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class SESAC_API UQuestEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

public:
	void SetMouseState(EEntryWidgetMouseState State);

protected:
	UTextBlock* mNameText;

	UImage* mSelect;
};
