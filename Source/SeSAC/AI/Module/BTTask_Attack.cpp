// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SeSAC/AI/AIPawn.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIPawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn<AAIPawn>();

	if (IsValid(AIPawn))
	{
		AIPawn->SetAIType(EAIType::Attack);
	}

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_Attack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::AbortTask(OwnerComp, NodeMemory);

	return Result;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// AI Pawn을 얻어옴
	AAIPawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn<AAIPawn>();
	if (!IsValid(AIPawn))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		AIPawn->SetAIType(EAIType::Idle);

		return;
	}

	// Target을 얻어옴
	auto Target = Cast<AActor>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (!IsValid(Target))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		AIPawn->SetAIType(EAIType::Idle);

		return;
	}

	// 공격거리를 빠져나갔는지 판단
	FVector AILocation = AIPawn->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();

	AILocation.Z -= AIPawn->GetCapsule()->GetScaledCapsuleHalfHeight();
	float Radius = AIPawn->GetCapsule()->GetScaledCapsuleRadius();

	auto TargetCapsule = Cast<UCapsuleComponent>(Target->GetRootComponent());
	if (IsValid(TargetCapsule))
	{
		TargetLocation.Z -= TargetCapsule->GetScaledCapsuleHalfHeight();
		Radius += TargetCapsule->GetScaledCapsuleRadius();
	}

	// 두 점 사이 거리 구함
	float Distance = FVector::Distance(AILocation, TargetLocation);

	if (Distance > 300.0f + Radius)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	else
	{
		// 회전
	}
}

void UBTTask_Attack::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
