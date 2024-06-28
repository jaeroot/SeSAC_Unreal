// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Sight.h"


AMonsterController::AMonsterController()
{
	PrimaryActorTick.bCanEverTick = true;

	mAIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

	// AI Controller는 PerceptionComponent를 등록할 수 있게 되어 있음
	SetPerceptionComponent(*mAIPerception);

	// 시야를 만들어줌
	mSightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	mSightConfig->SightRadius = 3000.0f;
	mSightConfig->LoseSightRadius = 3500.0f;
	mSightConfig->PeripheralVisionAngleDegrees = 90.0f;
	mSightConfig->DetectionByAffiliation.bDetectEnemies = true;
	mSightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	mSightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	// mSightConfig->SetMaxAge(0.0f);

	// 배열에 추가
	mAIPerception->ConfigureSense(*mSightConfig);

	// 대표 감각기관 설정
	mAIPerception->SetDominantSense(mSightConfig->GetSenseImplementation());

	// 
	mDamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageConfig"));
}

void AMonsterController::BeginPlay()
{
	Super::BeginPlay();


	mAIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AMonsterController::OnTargetDetect);
	mAIPerception->OnTargetPerceptionForgotten.AddDynamic(this, &AMonsterController::OnTargetForget);
}

void AMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AMonsterController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMonsterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterController::OnTargetDetect(AActor* Target, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("Target Detect"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("Target Detect Fail"));
	}
}

void AMonsterController::OnTargetForget(AActor* Target)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("TargetForget"));
}
