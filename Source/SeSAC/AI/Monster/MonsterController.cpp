// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"


AMonsterController::AMonsterController()
{
	PrimaryActorTick.bCanEverTick = true;

	// TeamID는 255개 팀이 있음
	// 아무것도 지정하지 않을 경우 255팀으로 기본 설정
	SetGenericTeamId(FGenericTeamId(3));

	// GetTeamAttitudeTowards()
	//ETeamAttitude

	mAIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

	// AI Controller는 PerceptionComponent를 등록할 수 있게 되어 있음
	SetPerceptionComponent(*mAIPerception);

	// 시야를 만들어줌
	mSightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	mSightConfig->SightRadius = 3000.0f;
	mSightConfig->LoseSightRadius = 3500.0f;
	mSightConfig->PeripheralVisionAngleDegrees = 90.0f;
	mSightConfig->DetectionByAffiliation.bDetectEnemies = true;
	mSightConfig->DetectionByAffiliation.bDetectNeutrals = false;
	mSightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	// mSightConfig->SetMaxAge(0.0f);

	// 배열에 추가
	mAIPerception->ConfigureSense(*mSightConfig);

	// 대표 감각기관 설정
	mAIPerception->SetDominantSense(mSightConfig->GetSenseImplementation());

	// 
	// mDamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageConfig"));


	// bt, bb
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		AITreeAsset(TEXT("/Game/AI/Monster/BT_MonsterDefault.BT_MonsterDefault"));
	if (AITreeAsset.Succeeded())
	{
		mAITree = AITreeAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData>
		BlackBoardAsset(TEXT("/Game/AI/Monster/BB_MonsterDefault.BB_MonsterDefault"));
	if (BlackBoardAsset.Succeeded())
	{
		mBlackboard = BlackBoardAsset.Object;
	}
	
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

	if (IsValid(mAITree) && IsValid(mBlackboard))
	{
		UBlackboardComponent* BlackboardRef = nullptr;
		if (UseBlackboard(mBlackboard, BlackboardRef))
		{
			// BehaviorTree를 동작시킴
			RunBehaviorTree(mAITree);
		}
	}
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
		AController* Controller = Cast<AController>(Target);
		if (IsValid(Controller))
		{
			Target = Controller->GetPawn<AActor>();
		}
		
		if (Target != Blackboard->GetValueAsObject((TEXT("Target"))))
		{
			Blackboard->SetValueAsObject(TEXT("Target"), Target);
			
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("Target Detect"));
		}
	}
	else
	{
		Blackboard->SetValueAsObject(TEXT("Target"), nullptr);
		
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("Target Detect Fail"));
	}
}

void AMonsterController::OnTargetForget(AActor* Target)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("TargetForget"));
}
