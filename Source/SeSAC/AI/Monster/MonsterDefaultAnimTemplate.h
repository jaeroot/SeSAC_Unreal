// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "SeSAC/AI/AIInfo.h"
#include "Animation/AnimInstance.h"
#include "MonsterDefaultAnimTemplate.generated.h"

UENUM(BlueprintType)
enum class EMonsterDefaultAnim : uint8
{
	Idle,
	Walk,
	Run,
	Attack,
	Death
};


UCLASS()
class SESAC_API UMonsterDefaultAnimTemplate : public UAnimInstance
{
	GENERATED_BODY()

public:
	/**
	 * 
	 */
	UMonsterDefaultAnimTemplate();

public:
	void ChangeAnim(EMonsterDefaultAnim Anim)
	{
		mMonsterAnim = Anim;
	}
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EMonsterDefaultAnim mMonsterAnim = EMonsterDefaultAnim::Idle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FString, UAnimSequence*> mSequenceMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FString, UBlendSpace*> mBlendSpaceMap;
};
