// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "Animation/AnimInstance.h"
#include "SelectPlayerAnimTemplate.generated.h"

UENUM(BlueprintType)
enum class ESelectPlayerAnim : uint8
{
	Idle,
	Select
};

UCLASS()
class SESAC_API USelectPlayerAnimTemplate : public UAnimInstance
{
	GENERATED_BODY()

public:
	USelectPlayerAnimTemplate();

public:
	void ChangeAnim(ESelectPlayerAnim Anim)
	{
		mAnim = Anim;
	}

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ESelectPlayerAnim mAnim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* mIdle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* mSelect;
	
};
