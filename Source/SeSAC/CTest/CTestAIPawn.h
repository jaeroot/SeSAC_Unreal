// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "GameFramework/Pawn.h"
#include "CTestAIPawn.generated.h"

class UFloatingPawnMovement;

UCLASS()
class SESAC_API ACTestAIPawn : public APawn
{
	GENERATED_BODY()

public:
	ACTestAIPawn();
	
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

protected:
	virtual void BeginPlay() override;

private:

public:

protected:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* mBody;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* mMesh;

	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* mMovement;

	float mHP = 100.0f;

private:

};
