// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "SeSAC/AI/AIInfo.h"
#include "AIController.h"
#include "MonsterController.generated.h"

struct FAIStimulus;
class UAISenseConfig_Damage;
class UAISenseConfig_Sight;

UCLASS()
class SESAC_API AMonsterController : public AAIController
{
	GENERATED_BODY()

public:
	AMonsterController();
	
	virtual void Tick(float DeltaTime) override;

	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	void SetTeamID(uint8 ID)
	{
		mTeamID = ID;
	}

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	UFUNCTION()
	void OnTargetDetect(AActor* Target, FAIStimulus Stimulus);
	
	UFUNCTION()
	void OnTargetForget(AActor* Target);

public:

protected:
	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* mAIPerception;

	UAISenseConfig_Sight* mSightConfig;
	UAISenseConfig_Damage* mDamageConfig;

	UBehaviorTree* mAITree;
	UBlackboardData* mBlackboard;

	uint8 mTeamID = 255;

};
