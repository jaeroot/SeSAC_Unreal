// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "GameFramework/PlayerState.h"
#include "SeSACPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FHPDelegate, float);

UCLASS()
class SESAC_API ASeSACPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ASeSACPlayerState();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	bool Damage(float Attack);
	

protected:
	UPROPERTY(VisibleAnywhere)
	FString mName;

	UPROPERTY(VisibleAnywhere)
	EPlayerJob mJob;
	
	UPROPERTY(VisibleAnywhere)
	float mAttack;
	
	UPROPERTY(VisibleAnywhere)
	float mDefense;
	
	UPROPERTY(VisibleAnywhere)
	float mHP;
	
	UPROPERTY(VisibleAnywhere)
	float mHPMax;
	
	UPROPERTY(VisibleAnywhere)
	float mMP;
	
	UPROPERTY(VisibleAnywhere)
	float mMPMax;
	
	UPROPERTY(VisibleAnywhere)
	float mMoveSpeed;
	
	UPROPERTY(VisibleAnywhere)
	float mAttackDistance;

	UPROPERTY(VisibleAnywhere)
	int32 mLevel;

	UPROPERTY(VisibleAnywhere)
	int32 mExp;

	UPROPERTY(VisibleAnywhere)
	int32 mGold;

	FHPDelegate mHPDelegate;

public:
	template <typename T>
	void AddHPDelegate(T* Obj, void (T::* Func)(float))
	{
		mHPDelegate.AddUObject(Obj, Func);
	}


private:
	static UDataTable* mPlayerInfoTable;
};
