// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"


DECLARE_MULTICAST_DELEGATE(FAIDeathDelegate);


UCLASS()
class SESAC_API AAIPawn : public APawn
{
	GENERATED_BODY()

public:
	AAIPawn();

	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UCapsuleComponent* GetCapsule() const
	{
		return mCapsule;
	}

	template <typename T>
	void AddDeathDelegate(T* Object, void(T::*Func)())
	{
		mDeathDelegate.AddUObject(Object, Func);
	}

public:

protected:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* mCapsule;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* mMesh;

	FAIDeathDelegate mDeathDelegate;
	
};