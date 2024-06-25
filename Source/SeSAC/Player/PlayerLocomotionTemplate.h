// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerLocomotionTemplate.generated.h"

/**
 * 
 */
UCLASS()
class SESAC_API UPlayerLocomotionTemplate : public UAnimInstance
{
	GENERATED_BODY()

public:
	void OnJump()
	{
		mJump = true;
	}
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mMoveSpeed = 0.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool mAcceleration = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool mIsAir = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mIdleAOPitch = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mIdleAOYaw = 0.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool mJump = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAnimSequence* mIdle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAnimSequence* mRunStart;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAnimSequence* mRun;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAnimSequence* mRunStop;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAnimSequence* mJumpStart;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAnimSequence* mJumpApex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAnimSequence* mFall;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAnimSequence* mFallRecovery;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBlendSpace* mIdleAO;
};
