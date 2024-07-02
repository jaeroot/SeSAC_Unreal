// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterPawn.h"

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
