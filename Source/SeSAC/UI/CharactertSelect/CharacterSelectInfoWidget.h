// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/UI/UIInfo.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectInfoWidget.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class SESAC_API UCharacterSelectInfoWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void SetPlayerImage(UMaterialInstance* Mtrl);
	void SetPlayerName(const FString& Name);

protected:
	UImage* mPlayerImage;

	UTextBlock* mPlayerName;
};
