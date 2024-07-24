// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInfoWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UItemInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mIcon = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));
	mItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	mItemContent = Cast<UTextBlock>(GetWidgetFromName(TEXT("Content")));
}
