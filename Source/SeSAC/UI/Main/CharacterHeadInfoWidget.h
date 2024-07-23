// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "CharacterHeadInfoWidget.generated.h"

class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class SESAC_API UCharacterHeadInfoWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	void SetPlayerName(const FString& Name);
	void SetHPPercent(float Percent);

protected:
	UTextBlock* mPlayerName;
	UProgressBar* mHPBar;
};
