// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "SeSAC/AI/AIPawn.h"
#include "MonsterPawn.generated.h"

class UMonsterMovement;

UCLASS()
class SESAC_API AMonsterPawn : public AAIPawn
{
	GENERATED_BODY()

public:
	AMonsterPawn();
	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:

protected:
	UPROPERTY(VisibleAnywhere)
	UMonsterMovement* mMovement;
};
