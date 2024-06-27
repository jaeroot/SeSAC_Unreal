// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

UCLASS()
class SESAC_API AAIPawn : public APawn
{
	GENERATED_BODY()

public:
	AAIPawn();

	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;

public:

protected:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* mCapsule;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* mMesh;

	
};
