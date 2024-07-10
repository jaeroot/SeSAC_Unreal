// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_Attack.h"

#include "KnightCharacter.h"

DEFINE_LOG_CATEGORY(LogAnimAttack);

UAnimNotifyState_Attack::UAnimNotifyState_Attack()
{
}

void UAnimNotifyState_Attack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                          float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	auto Character = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (IsValid(Character))
	{
		Character->AttackEnable();
	}
}

void UAnimNotifyState_Attack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	auto Character = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (IsValid(Character))
	{
		Character->AttackEnable();
	}
}

void UAnimNotifyState_Attack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
