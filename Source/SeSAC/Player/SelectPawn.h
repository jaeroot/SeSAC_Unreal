// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "GameFramework/Pawn.h"
#include "SelectPawn.generated.h"

enum class ESelectPlayerAnim : uint8;
class USelectPlayerAnimTemplate;

UCLASS()
class SESAC_API ASelectPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASelectPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void OnMouse(bool Overlap);

	EPlayerJob GetJob() const
	{
		return mJob;
	}

	void ChangeAnim(ESelectPlayerAnim Anim);

protected:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* mCapsule;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* mMesh;

	UPROPERTY(EditAnywhere)
	EPlayerJob mJob;

	USelectPlayerAnimTemplate* mAnim;
	
};
