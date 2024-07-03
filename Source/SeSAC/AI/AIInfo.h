#pragma once

#include "AIInfo.generated.h"

enum class EAIType : uint8
{
	Idle,
	Patrol,
	Trace,
	Attack,
	Death
};


class CMonsterDefaultKey
{
public:
	static FName mTarget;
	static FName mAttackEnd;
	static FName mPatrolPoint;
	static FName mPatrolEnable;
};


USTRUCT(BlueprintType)
struct FMonsterAnimData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FString, UAnimSequence*> mSequenceMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FString, UBlendSpace*> mBlendSpaceMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FString, UAnimMontage*> mMontageMap;
};

USTRUCT(BlueprintType)
struct FMonsterInfoTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString mName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mDefense;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mHP;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mMP;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mMoveSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mAttackDistance;	
};