// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "StartPlayerController.generated.h"

class UStartWidget;
/**
 * 
 */
UCLASS()
class SESAC_API AStartPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AStartPlayerController();

protected:
	virtual void BeginPlay() override;

protected:
	TSubclassOf<UStartWidget> mWidgetClass;
	UStartWidget* mWidget;
	
};
