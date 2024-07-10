// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_Attack.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogAnimAttack, Log, All);

UCLASS(editinlinenew, Blueprintable, const, hidecategories=Object, collapsecategories, meta=(ShowWorldContextPin,  DisplayName = "Attack"))
class SESAC_API UAnimNotifyState_Attack : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UAnimNotifyState_Attack();

	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference) override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	FName FirstSocketName = NAME_None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	FName SecondSocketName = NAME_None;
	
public:
	
};
