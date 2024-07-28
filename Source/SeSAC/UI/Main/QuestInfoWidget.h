// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/UI/UIInfo.h"
#include "SeSAC/GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "QuestInfoWidget.generated.h"

class UListView;
class UTextBlock;
/**
 * 
 */
UCLASS()
class SESAC_API UQuestInfoWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void SetData(class UQuestData* Data);
	void ClearData();

protected:
	UFUNCTION()
	void AcceptButtonClick();

protected:
	UTextBlock* mNameText;
	UTextBlock* mContentText;
	UListView* mClearList;
	UButton* mAcceptButton;
};
