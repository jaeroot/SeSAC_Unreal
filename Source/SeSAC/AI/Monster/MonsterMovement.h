// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "MonsterMovement.generated.h"


UCLASS()
class SESAC_API UMonsterMovement : public UFloatingPawnMovement
{
	GENERATED_BODY()

public:
	UMonsterMovement();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

public:

	
};
