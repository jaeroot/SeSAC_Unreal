// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "MonsterPawn.h"
#include "MinionPawn.generated.h"

UCLASS()
class SESAC_API AMinionPawn : public AMonsterPawn
{
	GENERATED_BODY()

public:
	AMinionPawn();
	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
};
