// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "GameFramework/Actor.h"
#include "CTestBullet.generated.h"

class UProjectileMovementComponent;

UCLASS()
class SESAC_API ACTestBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ACTestBullet();
	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void ProjectileHit(const FHitResult& HitResult);

public:
	void SetOwnerController(AController* Controller)
	{
		mOwnerController = Controller;
	}

	void SetDamage(float Damage)
	{
		mDamage = Damage;
	}

protected:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* mBody;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mMesh;
	
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* mMovement;

	float mDistance = 2000.0f;

	FVector mPrevLocation;

	AController* mOwnerController;
	float mDamage = 10.0f;

};
