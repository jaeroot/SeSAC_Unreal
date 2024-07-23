// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "SeSAC/UI/UIInfo.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

class UInventoryListWidget;
class UPlayerHUDWidget;
/**
 * 
 */
UCLASS()
class SESAC_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void SetPlayerName(const FString& Name);
	void SetHPPercent(float Percent);
	void SetMPPercent(float Percent);

protected:
	UFUNCTION()
	void CharacterStateButtonClick();
	UFUNCTION()
	void InventoryButtonClick();
	UFUNCTION()
	void SkillButtonClick();
	UFUNCTION()
	void OptionButtonClick();

protected:
	UPlayerHUDWidget* mPlayerHUD;
	UInventoryListWidget* mInventory;

	UButton* mCharacterStateButton;
	UButton* mInventoryButton;
	UButton* mSkillButton;
	UButton* mOptionButton;
};
