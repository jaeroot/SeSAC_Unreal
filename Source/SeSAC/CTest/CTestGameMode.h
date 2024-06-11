// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "CTestGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SESAC_API ACTestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACTestGameMode();

public:
	FORCEINLINE void AddScore(int32 Score)
	{
		mScore += Score;

		UE_LOG(SeSAC, Warning, TEXT("Score : %d"), mScore);
	}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 mScore = 0;
};
