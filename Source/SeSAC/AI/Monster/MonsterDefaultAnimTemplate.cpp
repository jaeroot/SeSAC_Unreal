// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterDefaultAnimTemplate.h"

#include "AIController.h"
#include "MonsterDataManager.h"
#include "MonsterPawn.h"
#include "BehaviorTree/BlackboardComponent.h"

UMonsterDefaultAnimTemplate::UMonsterDefaultAnimTemplate()
{

}

void UMonsterDefaultAnimTemplate::SetAnimData(const FName& Key)
{
	const FMonsterAnimData* AnimData = CMonsterDataManager::GetInst()->FindMonsterAnim(Key);
	if (AnimData)
	{
		mSequenceMap = AnimData->mSequenceMap;
		mBlendSpaceMap = AnimData->mBlendSpaceMap;
		mMontageMap = AnimData->mMontageMap;
	}
}

void UMonsterDefaultAnimTemplate::PlayMontage(const FString& Name)
{
	UAnimMontage** Montage = mMontageMap.Find(Name);

	if (Montage)
	{
		if (!Montage_IsPlaying(*Montage))
		{
			if (Name == TEXT("Hit"))
			{
				mHitAlpha = 1.0f;
			}
			
			Montage_SetPosition(*Montage, 0.0f);
			Montage_Play(*Montage);
		}
	}
}

void UMonsterDefaultAnimTemplate::AnimNotify_Attack()
{
	auto Monster = Cast<AMonsterPawn>(TryGetPawnOwner());
	if (IsValid(Monster))
	{
		Monster->Attack();
	}
}

void UMonsterDefaultAnimTemplate::AnimNotify_AttackEnd()
{
	UBlackboardComponent* BlackBoard = TryGetPawnOwner()->GetController<AAIController>()->GetBlackboardComponent();
	BlackBoard->SetValueAsBool(CMonsterDefaultKey::mAttackEnd, true);
}

void UMonsterDefaultAnimTemplate::AnimNotify_DeathEnd()
{
	auto Monster = Cast<AMonsterPawn>(TryGetPawnOwner());
	if (IsValid(Monster))
	{
		Monster->SetDissolveEnalbe(true);
	}
}

void UMonsterDefaultAnimTemplate::AnimNotify_HitEnd()
{
	mHitAlpha = 0.0f;
}
