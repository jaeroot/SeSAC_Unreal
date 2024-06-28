// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"

#include "AISpawnActor.generated.h"

class AAIPawn;

UCLASS()
class SESAC_API AAISpawnActor : public AActor
{
	GENERATED_BODY()

public:
	AAISpawnActor();
	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	void Spawn();

	UFUNCTION()
	void AIDeathDelegate();
	
public:

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* mRoot;
	
#if WITH_EDITORONLY_DATA
	UPROPERTY()
	UArrowComponent* mArrow;
#endif

	UPROPERTY(EditAnywhere)
	TSubclassOf<AAIPawn> mSpawnClass;

	AAIPawn* mSpawnActor = nullptr;

	UPROPERTY(EditAnywhere)
	float mSpawnTime = 0.0f;

	float mCalculateSpawnTime = 0.0f;
};
