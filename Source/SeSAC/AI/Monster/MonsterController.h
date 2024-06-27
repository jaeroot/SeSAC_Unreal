// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "AIController.h"
#include "MonsterController.generated.h"

UCLASS()
class SESAC_API AMonsterController : public AAIController
{
	GENERATED_BODY()

public:
	AMonsterController();
	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:

protected:
	UPROPERTY(EditAnywhere)
	UAIPerceptionComponent* mAIPerception;
};
