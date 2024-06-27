// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerMovingAttackTemplate.generated.h"

/**
 * 
 */
UCLASS()
class SESAC_API UPlayerMovingAttackTemplate : public UAnimInstance
{
	GENERATED_BODY()


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> mAttackMontage;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> mAttackRecoveryMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> mAttackSectionArray;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 mCurrentAttackSection = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName mAttackAirSection;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool mAcceleration = false;
	
	bool mAttackCombo = false;
	bool mAttackState = false;
};
