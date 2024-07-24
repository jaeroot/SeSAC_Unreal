// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/IUserObjectListEntry.h"
#include "SeSAC/UI/UIInfo.h"
#include "SeSAC/GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "InventoryListEntryWidget.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class SESAC_API UInventoryListEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

public:
	void SetMouseState(EEntryWidgetMouseState State);

protected:
	UImage* mIcon;
	UTextBlock* mNameText;
	UTextBlock* mCountText;
	UImage* mSelect;
};
