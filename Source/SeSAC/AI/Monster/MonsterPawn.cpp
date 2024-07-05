// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterPawn.h"

#include "BrainComponent.h"
#include "MonsterController.h"
#include "MonsterDataManager.h"
#include "MonsterMovement.h"


AMonsterPawn::AMonsterPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	mMovement = CreateDefaultSubobject<UMonsterMovement>(TEXT("Movement"));
	mMovement->SetUpdatedComponent(RootComponent);

	mCapsule->SetCollisionProfileName(TEXT("Monster"));

	AIControllerClass = AMonsterController::StaticClass();
}

void AMonsterPawn::BeginPlay()
{
	Super::BeginPlay();

	const FMonsterInfoTable* Info = CMonsterDataManager::GetInst()->FindMonsterInfo(mMonsterInfoKey);

	if (Info)
	{
		mAttack = Info->mAttack;
		mDefense = Info->mDefense;
		mHP = Info->mHP;
		mHPMax = Info->mHP;
		mMP = Info->mMP;
		mMPMax = Info->mMP;
		mMoveSpeed = Info->mMoveSpeed;
		mAttackDistance = Info->mAttackDistance;
	}
}

void AMonsterPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
}

float AMonsterPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	mHP -= DamageAmount * 0.25f;

	if (mHP <= 0.0f)
	{
		for (auto Mtrl : mMaterialDynamicArray)
		{
			Mtrl->SetScalarParameterValue(TEXT("DissolveEnable"), 1.0f);
		}
		
		SetAIType(EAIType::Death);

		// 비헤이비어 트리 정지
		AAIController* AIControl = GetController<AAIController>();

		if (IsValid(AIControl))
		{
			AIControl->GetBrainComponent()->StopLogic(("Death"));
		}

		// Destroy();
	}
	else
	{
		// Hit 처리
		for (auto Mtrl : mMaterialDynamicArray)
		{
			Mtrl->SetScalarParameterValue(TEXT("HitEnable"), 1.0f);
		}
		
		GetWorld()->GetTimerManager().SetTimer(mHitTimer, this, &AMonsterPawn::HitEnd, mHitTime);
	}

	return DamageAmount;
}

void AMonsterPawn::HitEnd()
{
	for (auto Mtrl : mMaterialDynamicArray)
	{
		Mtrl->SetScalarParameterValue(TEXT("HitEnable"), 0.0f);
	}
	
	GetWorld()->GetTimerManager().ClearTimer(mHitTimer);
}

void AMonsterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AMonsterController* MonsterController = Cast<AMonsterController>(NewController);

	if (IsValid(MonsterController))
	{
		MonsterController->SetTeamID(mTeamID);
	}
}

void AMonsterPawn::SetAIType(EAIType Type)
{
	Super::SetAIType(Type);
}

void AMonsterPawn::Attack()
{
}
