// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
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

};
