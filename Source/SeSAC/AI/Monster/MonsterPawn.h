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
	virtual void PossessedBy(AController* NewController) override;

public:
	virtual void SetAIType(EAIType Type) override;

	virtual void Attack();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:

protected:
	UPROPERTY(VisibleAnywhere)
	UMonsterMovement* mMovement;

	FName mMonsterInfoKey;
	float mAttack;
	float mDefense;
	float mHP;
	float mHPMax;
	float mMP;
	float mMPMax;
	float mMoveSpeed;
	float mAttackDistance;
};
