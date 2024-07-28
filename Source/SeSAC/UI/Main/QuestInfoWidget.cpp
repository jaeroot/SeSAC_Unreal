// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestInfoWidget.h"

#include "QuestClearDataObject.h"
#include "QuestData.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"

void UQuestInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("QuestName")));
	mContentText = Cast<UTextBlock>(GetWidgetFromName(TEXT("QuestContent")));
	mClearList = Cast<UListView>(GetWidgetFromName(TEXT("QuestClearList")));
	mAcceptButton = Cast<UButton>(GetWidgetFromName(TEXT("AcceptButton")));
	mAcceptButton->OnClicked.AddDynamic(this, &UQuestInfoWidget::AcceptButtonClick);
}

void UQuestInfoWidget::SetData(UQuestData* Data)
{
	mNameText->SetText(FText::FromString(Data->mData.Name));
	mContentText->SetText(FText::FromString(Data->mData.Content));

	// 목록 전부 제거
	mClearList->ClearListItems();

	for (auto& ClearData : Data->mData.ClearArray)
	{
		UQuestClearDataObject* Obj = NewObject<UQuestClearDataObject>();

		Obj->mClearData.Type = ClearData.Type;
		Obj->mClearData.ClearName = ClearData.ClearName;
		Obj->mClearData.ClearCount = ClearData.ClearCount;
		Obj->mClearData.ClearCountMax = ClearData.ClearCountMax;
		
		mClearList->AddItem(Obj);
	}

	mAcceptButton->SetVisibility(ESlateVisibility::Visible);
}

void UQuestInfoWidget::ClearData()
{
	mNameText->SetText(FText::FromString(TEXT("")));
	mContentText->SetText(FText::FromString(TEXT("")));
	
	// 목록 전부 제거
	mClearList->ClearListItems();

	mAcceptButton->SetVisibility(ESlateVisibility::Collapsed);
}

void UQuestInfoWidget::AcceptButtonClick()
{
}
