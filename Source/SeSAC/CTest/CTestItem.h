// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "GameFramework/Actor.h"
#include "CTestItem.generated.h"

UCLASS()
class SESAC_API ACTestItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ACTestItem();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void CollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
public:

protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* mBody;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mMesh;
	

};
