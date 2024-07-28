// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestEntryWidget.h"

#include "QuestData.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UQuestEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	mSelect = Cast<UImage>(GetWidgetFromName(TEXT("Select")));
}

void UQuestEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UQuestData* Data = Cast<UQuestData>(ListItemObject);

	if (IsValid(Data))
	{
		mNameText->SetText(FText::FromString(Data->mData.Name));

		UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(mNameText->Slot);
		PanelSlot->SetPosition(FVector2D(Data->mTreeLevel * 30.0f, 0.0f));
	}
}

void UQuestEntryWidget::SetMouseState(EEntryWidgetMouseState State)
{
	switch (State)
	{
	case EEntryWidgetMouseState::None:
		mSelect->SetVisibility(ESlateVisibility::Collapsed);
		mSelect->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
		break;
	case EEntryWidgetMouseState::MouseOn:
		mSelect->SetVisibility(ESlateVisibility::Visible);
		mSelect->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 0.0f, 0.3f));
		break;
	case EEntryWidgetMouseState::Select:
		mSelect->SetVisibility(ESlateVisibility::Visible);
		mSelect->SetColorAndOpacity(FLinearColor(1.0f, 0.0f, 0.0f, 0.3f));
		break;
	}
}
