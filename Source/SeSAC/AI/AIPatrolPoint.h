// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "GameFramework/Actor.h"
#include "AIPatrolPoint.generated.h"

UCLASS()
class SESAC_API AAIPatrolPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AAIPatrolPoint();
	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:	

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* mRoot;
	
#if WITH_EDITORONLY_DATA
	UPROPERTY()
	UArrowComponent* mArrow;
#endif
	
};
