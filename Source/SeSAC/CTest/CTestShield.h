// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "GameFramework/Actor.h"
#include "CTestShield.generated.h"

UCLASS()
class SESAC_API ACTestShield : public AActor
{
	GENERATED_BODY()
	
public:	
	ACTestShield();
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;

	
public:
	
protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mMesh;

};
