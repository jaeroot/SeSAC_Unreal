// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GenericTeamAgentInterface.h"
#include "SeSAC/GameInfo.h"
#include "SeSAC/AI/AIInfo.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"


class UMonsterDefaultAnimTemplate;
DECLARE_MULTICAST_DELEGATE(FAIDeathDelegate);


UCLASS()
class SESAC_API AAIPawn : public APawn, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AAIPawn();

	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void PossessedBy(AController* NewController) override;
	
protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	const FString& GetAIName() const
	{
		return mName;
	}
	
	UCapsuleComponent* GetCapsule() const
	{
		return mCapsule;
	}

	EAIType GetAIType() const
	{
		return mAIType;
	}

	void SetAIName(const FString& Name)
	{
		mName = Name;
	}

	virtual void SetAIType(EAIType Type);

	template <typename T>
	void AddDeathDelegate(T* Object, void(T::*Func)())
	{
		mDeathDelegate.AddUObject(Object, Func);
	}
	
	void SetTeamID(uint8 TeamID)
	{
		mTeamID = TeamID;
	}
	virtual FGenericTeamId GetGenericTeamId() const override;

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

public:

protected:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* mCapsule;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* mMesh;

	FString mName;

	FAIDeathDelegate mDeathDelegate;

	uint8 mTeamID = 10;

	EAIType mAIType;	
};
