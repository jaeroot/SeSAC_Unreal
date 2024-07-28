// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/UI/UIInfo.h"
#include "SeSAC/GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "QuestWidget.generated.h"

class UQuestData;
class UQuestInfoWidget;
class UTreeView;
/**
 * 
 */
UCLASS()
class SESAC_API UQuestWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UQuestWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void GetItemChildren(UObject* Data, TArray<UObject*>& ChildArray);
	
	UFUNCTION()
	void CloseButtonClick();

	UFUNCTION()
	void TreeItemClick(UObject* Item);

	UFUNCTION()
	void TreeItemHovered(UObject* Item, bool Hovered);

	UFUNCTION()
	void TreeItemSelect(UObject* Item);

protected:
	UButton* mCloseButton;
	UButton* mTitleBar;
	UTreeView* mMenu;
	UQuestInfoWidget* mInfo;
	UDataTable* mQuestTable;
	
	UQuestData* mSelectQuest = nullptr;
};
