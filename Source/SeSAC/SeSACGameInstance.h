// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "SeSACGameInstance.generated.h"

enum class EPlayerJob : uint8;
/**
 * 
 */
UCLASS()
class SESAC_API USeSACGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	USeSACGameInstance();

public:
	virtual void Init() override;

public:
	EPlayerJob GetSelectJob() const
	{
		return mSelectJob;
	}

	const FString& GetPlayerName() const
	{
		return mPlayerName;
	}
	
	void SetSelectJob(EPlayerJob Job)
	{
		mSelectJob = Job;
	}

	void SetPlayerName(const FString& Name)
	{
		mPlayerName = Name;
	}

protected:
	EPlayerJob mSelectJob = EPlayerJob::Knight;
	FString mPlayerName = TEXT("Player");
};
