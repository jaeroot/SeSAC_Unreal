// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestClearDataEntryWidget.h"

#include "QuestClearDataObject.h"
#include "Components/TextBlock.h"

void UQuestClearDataEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	mCountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CountText")));
}

void UQuestClearDataEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UQuestClearDataObject* Data = Cast<UQuestClearDataObject>(ListItemObject);

	mNameText->SetText(FText::FromString(Data->mClearData.ClearName));

	FString CountText = FString::Printf(TEXT("%d / %d"), Data->mClearData.ClearCount, Data->mClearData.ClearCountMax);
	mCountText->SetText(FText::FromString(CountText));
}
