// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CircularSectorDecal.generated.h"

UCLASS()
class SESAC_API ACircularSectorDecal : public AActor
{
	GENERATED_BODY()
	
public:	
	ACircularSectorDecal();
	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* mRoot;

	UPROPERTY(VisibleAnywhere)
	UDecalComponent* mDecal;

	UMaterialInstanceDynamic* mDynamicMaterial;

	UPROPERTY(EditAnywhere)
	float SectorCount = 6.0f;

	UPROPERTY(EditAnywhere)
	float RangeTime = 5.0f;

	UPROPERTY(VisibleAnywhere)
	float Radius = 0.0f;
	float RangeTimeAcc = 0.0f;
};
