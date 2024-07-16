// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectInfoWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UCharacterSelectInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mPlayerImage = Cast<UImage>(GetWidgetFromName(TEXT("PlayerImage")));
	mPlayerName = Cast<UTextBlock>(GetWidgetFromName(TEXT("PlayerName")));
}

void UCharacterSelectInfoWidget::SetPlayerImage(UMaterialInstance* Mtrl)
{
	mPlayerImage->SetBrushFromMaterial(Mtrl);
}

void UCharacterSelectInfoWidget::SetPlayerName(const FString& Name)
{
	mPlayerName->SetText(FText::FromString(Name));
}
