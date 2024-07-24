// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/UI/UIInfo.h"
#include "SeSAC/GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "ItemInfoWidget.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class SESAC_API UItemInfoWidget : public UUserWidget
{
	GENERATED_BODY()

	friend class UInventoryTileWidget;

protected:
	virtual void NativeConstruct() override;

protected:
	UImage* mIcon;
	UTextBlock* mItemName;
	UTextBlock* mItemContent;
};
