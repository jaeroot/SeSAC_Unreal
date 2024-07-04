// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "GameFramework/Actor.h"
#include "DecalBase.generated.h"

UCLASS()
class SESAC_API ADecalBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ADecalBase();
	
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;

public:
	void SetOriginMaterial(UMaterialInterface* Material);

public:	

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* mRoot;

	UPROPERTY(VisibleAnywhere)
	UDecalComponent* mDecal;

	UMaterialInstanceDynamic* mDynamicMaterial;

	float mOpacity = 1.0f;
	float mGlow = 0.0f;
};
