// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestWidget.h"

#include "QuestData.h"
#include "QuestEntryWidget.h"
#include "QuestInfoWidget.h"
#include "Components/TreeView.h"

UQuestWidget::UQuestWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable>
		QuestTable(TEXT("/Game/UI/Quest/DT_Quest.DT_Quest"));
	
	if (QuestTable.Succeeded())
	{
		mQuestTable = QuestTable.Object;
	}
}

void UQuestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mCloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));
	mTitleBar = Cast<UButton>(GetWidgetFromName(TEXT("TitleBar")));
	mMenu = Cast<UTreeView>(GetWidgetFromName(TEXT("Menu")));
	mInfo = Cast<UQuestInfoWidget>(GetWidgetFromName(TEXT("WB_QuestInfo")));

	mMenu->OnItemClicked().AddUObject(this, &UQuestWidget::TreeItemClick);
	mMenu->OnItemIsHoveredChanged().AddUObject(this, &UQuestWidget::TreeItemHovered);
	mMenu->OnItemSelectionChanged().AddUObject(this, &UQuestWidget::TreeItemSelect);
	

	mMenu->SetOnGetItemChildren(this, &UQuestWidget::GetItemChildren);

	TArray<FQuestInfo*> QuestInfoArray;
	mQuestTable->GetAllRows<FQuestInfo>(TEXT(""), QuestInfoArray);

	UQuestData* Data = NewObject<UQuestData>();
	Data->mData.Name = TEXT("Main");
	Data->mData.QuestEnable = false;
	for (auto QuestInfo : QuestInfoArray)
	{
		if (QuestInfo->QuestType == EQuestType::Main)
		{
			Data->CreateChild(QuestInfo);
		}
	}
	mMenu->AddItem(Data);

	Data = NewObject<UQuestData>();
	Data->mData.Name = TEXT("Sub");
	Data->mData.QuestEnable = false;
	for (auto QuestInfo : QuestInfoArray)
	{
		if (QuestInfo->QuestType == EQuestType::Sub)
		{
			Data->CreateChild(QuestInfo);
		}
	}
	mMenu->AddItem(Data);
}

void UQuestWidget::GetItemChildren(UObject* Data, TArray<UObject*>& ChildArray)
{
	UQuestData* QuestData = Cast<UQuestData>(Data);

	ChildArray = QuestData->mChildArray;
}

void UQuestWidget::CloseButtonClick()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UQuestWidget::TreeItemClick(UObject* Item)
{
	UQuestData* Data = Cast<UQuestData>(Item);

	if (IsValid(Data))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Magenta, Data->mData.Name);
	}
}

void UQuestWidget::TreeItemHovered(UObject* Item, bool Hovered)
{
	UQuestData* Data = Cast<UQuestData>(Item);

	if (mSelectQuest != Item)
	{
		Data->mOnMouse = Hovered;

		UQuestEntryWidget* EntryWidget = mMenu->GetEntryWidgetFromItem<UQuestEntryWidget>(Item);
		if (IsValid(EntryWidget))
		{
			if (Hovered)
			{
				EntryWidget->SetMouseState(EEntryWidgetMouseState::MouseOn);
			}
			else
			{
				EntryWidget->SetMouseState(EEntryWidgetMouseState::None);
			}
		}
	}
}

void UQuestWidget::TreeItemSelect(UObject* Item)
{
	// 기존에 선택된 아이템이 있을 경우, 이 아이템은 None으로 만들어줌
	if (IsValid(mSelectQuest))
	{
		mSelectQuest->mSelect = false;

		UQuestEntryWidget* EntryWidget = mMenu->GetEntryWidgetFromItem<UQuestEntryWidget>(mSelectQuest);
		if (IsValid(EntryWidget))
		{
			EntryWidget->SetMouseState(EEntryWidgetMouseState::None);
		}
	}

	mSelectQuest = Cast<UQuestData>(Item);
	
	// 새로 선택한 아이템을 선택 상태로 만들어줌
	if (IsValid(mSelectQuest))
	{
		mSelectQuest->mSelect = true;

		UQuestEntryWidget* EntryWidget = mMenu->GetEntryWidgetFromItem<UQuestEntryWidget>(mSelectQuest);
		if (IsValid(EntryWidget))
		{
			EntryWidget->SetMouseState(EEntryWidgetMouseState::Select);
		}

		if (mSelectQuest->mData.QuestEnable)
		{
			mInfo->SetData(mSelectQuest);
		}
		else
		{
			mInfo->ClearData();
		}
	}
	else
	{
		mInfo->ClearData();
	}
}
