// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "SeSAC/AI/AIInfo.h"

/**
 * 
 */
class SESAC_API CMonsterDataManager
{
private:
	CMonsterDataManager();
	~CMonsterDataManager();

private:
	UDataTable* mMonsterAnimTable = nullptr;
	UDataTable* mMonsterInfoTable = nullptr;

public:
	bool Init();

	const FMonsterAnimData* FindMonsterAnim(const FName& Key);
	const FMonsterInfoTable* FindMonsterInfo(const FName& Key);

private:
	static CMonsterDataManager* mInst;

public:
	static CMonsterDataManager* GetInst()
	{
		if (!mInst)
		{
			mInst = new CMonsterDataManager;
		}
		
		return mInst;
	}

	static void Destroy()
	{
		if (mInst)
		{
			delete mInst;
			mInst = nullptr;
		}
	}
};
