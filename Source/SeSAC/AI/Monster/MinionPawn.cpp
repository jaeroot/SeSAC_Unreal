// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionPawn.h"

#include "MonsterDefaultAnimTemplate.h"


AMinionPawn::AMinionPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Game/ParagonMinions/Characters/Minions/Down_Minions/Meshes/Minion_Lane_Melee_Dawn.Minion_Lane_Melee_Dawn"));

	if (MeshAsset.Succeeded())
	{
		mMesh->SetSkeletalMeshAsset(MeshAsset.Object);
	}

	mCapsule->SetCapsuleHalfHeight(86.0f);
	mCapsule->SetCapsuleRadius(50.0f);
	mMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -86.0f));
	mMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		MinionAnim(TEXT("/Game/AI/Monster/ABP_Minion.ABP_Minion_C"));
	if (MinionAnim.Succeeded())
	{
		mMesh->SetAnimInstanceClass(MinionAnim.Class);
	}
	
}

void AMinionPawn::BeginPlay()
{
	Super::BeginPlay();

	mMinionAnim = Cast<UMonsterDefaultAnimTemplate>(mMesh->GetAnimInstance());
}

void AMinionPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMinionPawn::SetAIType(EAIType Type)
{
	Super::SetAIType(Type);

	EMonsterDefaultAnim Anim = EMonsterDefaultAnim::Idle;

	switch (mAIType)
	{
	case EAIType::Idle:
		Anim = EMonsterDefaultAnim::Idle;
		break;
	case EAIType::Patrol:
		Anim = EMonsterDefaultAnim::Walk;
		break;
	case EAIType::Trace:
		Anim = EMonsterDefaultAnim::Run;
		break;
	case EAIType::Attack:
		Anim = EMonsterDefaultAnim::Attack;
		break;
	case EAIType::Death:
		Anim = EMonsterDefaultAnim::Death;
		break;
	}

	mMinionAnim->ChangeAnim(Anim);
}
