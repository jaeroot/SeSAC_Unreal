// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SESAC_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativePostEvaluateAnimation() override;
	virtual void NativeUninitializeAnimation() override;

	virtual void NativeBeginPlay() override;

public:
	void SetMoveDir(const FVector& ActionValue);

	void PlayAttackMontage();

	// 애니메이션 노티파이 함수는 void AnimNotify_노티파이이름() 으로 함수를 만들어줘야함
	UFUNCTION()
	void AnimNotify_AttackCombo();
	UFUNCTION()
	void AnimNotify_AttackComboEnd();
	
	UFUNCTION()
	void AnimNotify_AttackEnable();
	UFUNCTION()
	void AnimNotify_AttackDisable();
	
protected:
	// bInterrupted = true if it was not property finished
	UFUNCTION()
	void MontageEnd(UAnimMontage* Montage, bool bInterrupted);

	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mMoveSpeed = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mMoveDir = 0.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool mAcceleration = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool mIsAir = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mIdleAOPitch = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mIdleAOYaw = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> mAttackMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> mAttackRecoveryMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> mAttackSectionArray;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 mCurrentAttackSection = 0;

	bool mAttackCombo = false;
	bool mAttackState = false;
};
