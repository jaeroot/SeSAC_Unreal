// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "InGamePlayerController.generated.h"

class UMainWidget;
/**
 * 
 */
UCLASS()
class SESAC_API AInGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AInGamePlayerController();

protected:
	virtual void BeginPlay() override;

public:
	void SetPlayerName(const FString& Name);
	void SetHPPercent(float Percent);
	void SetMPPercent(float Percent);

protected:
	TSubclassOf<UMainWidget> mWidgetClass;
	UMainWidget* mWidget;
};
