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
public:
	virtual void SetAIType(EAIType Type) override;

	virtual void Attack() override;

protected:
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
public:

protected:
	UMonsterDefaultAnimTemplate* mMinionAnim;

	UParticleSystem* mAttackParticle;
};
