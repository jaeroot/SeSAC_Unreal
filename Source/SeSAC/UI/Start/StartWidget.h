// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/UI/UIInfo.h"
#include "Blueprint/UserWidget.h"
#include "StartWidget.generated.h"

/**
 * 
 */
UCLASS()
class SESAC_API UStartWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION()
	void StartClick();
	UFUNCTION()
	void StartHovered();
	UFUNCTION()
	void StartUnHovered();
	
	UFUNCTION()
	void ExitClick();
	UFUNCTION()
	void ExitHovered();
	UFUNCTION()
	void ExitUnHovered();

protected:
	UButton* mStartButton;
	UButton* mExitButton;

	UPROPERTY(EditAnywhere)
	FName mNextLevelName;

	TMap<FString, UWidgetAnimation*> mAnimMap;
	UWidgetAnimation* mStartButtonScale;
	UWidgetAnimation* mExitButtonScale;
	UWidgetAnimation* mStartAnim;
};
