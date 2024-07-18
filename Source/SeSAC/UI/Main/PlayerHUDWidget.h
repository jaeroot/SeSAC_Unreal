// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "SeSAC/UI/UIInfo.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

class UTextBlock;
class UProgressBar;
class UImage;
/**
 * 
 */
UCLASS()
class SESAC_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void SetPlayerName(const FString& Name);
	void SetHPPercent(float Percent);
	void SetMPPercent(float Percent);

protected:
	UImage* mImage;
	UTextBlock* mPlayerName;
	UProgressBar* mHPBar;
	UProgressBar* mMPBar;
};
