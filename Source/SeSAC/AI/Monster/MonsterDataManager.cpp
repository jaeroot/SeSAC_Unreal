// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterDataManager.h"

CMonsterDataManager* CMonsterDataManager::mInst = nullptr;

CMonsterDataManager::CMonsterDataManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>
		MonsterAnimTable(TEXT("/Game/AI/Monster/DT_MonsterAnim.DT_MonsterAnim"));
	
	if (MonsterAnimTable.Succeeded())
	{
		mMonsterAnimTable = MonsterAnimTable.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable>
		MonsterInfoTable(TEXT("/Game/AI/Monster/DT_MonsterInfo.DT_MonsterInfo"));

	if (MonsterAnimTable.Succeeded())
	{
		mMonsterInfoTable = MonsterInfoTable.Object;
	}		
}

CMonsterDataManager::~CMonsterDataManager()
{
}

bool CMonsterDataManager::Init()
{
	return true;
}

const FMonsterAnimData* CMonsterDataManager::FindMonsterAnim(const FName& Key)
{
	return mMonsterAnimTable->FindRow<FMonsterAnimData>(Key, TEXT(""));
}

const FMonsterInfoTable* CMonsterDataManager::FindMonsterInfo(const FName& Key)
{
	return mMonsterInfoTable->FindRow<FMonsterInfoTable>(Key, TEXT(""));
}
