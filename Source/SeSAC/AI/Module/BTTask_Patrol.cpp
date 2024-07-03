// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Patrol.h"

#include "AIController.h"
#include "SeSAC/AI/AIPawn.h"

UBTTask_Patrol::UBTTask_Patrol()
{
	NodeName = TEXT("Patrol");
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result =  Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIPawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn<AAIPawn>();

	if (IsValid(AIPawn))
	{
		AIPawn->SetAIType(EAIType::Patrol);
	}

	return Result;
}

EBTNodeResult::Type UBTTask_Patrol::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::AbortTask(OwnerComp, NodeMemory);

	return Result;
} 

void UBTTask_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

void UBTTask_Patrol::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	AAIPawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn<AAIPawn>();
	if (IsValid(AIPawn))
	{
		AIPawn->NextPatrolPoint();
		AIPawn->RegisterPatrolPoint();

		AIPawn->SetAIType(EAIType::Idle);
	}
}
