// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SeSAC/AI/AIPatrolPoint.h"


AAIPawn::AAIPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(mCapsule);
	
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mMesh->SetupAttachment(mCapsule);
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationYaw = true;
}

void AAIPawn::BeginPlay()
{
	Super::BeginPlay();

}

void AAIPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// 등록된 함수가 있을 경우, 해당 함수들을 호출함
	if (mDeathDelegate.IsBound())
	{
		mDeathDelegate.Broadcast();
	}
}

void AAIPawn::SetAIType(EAIType Type)
{
	mAIType = Type;
}

FGenericTeamId AAIPawn::GetGenericTeamId() const
{
	return FGenericTeamId(mTeamID);
}

ETeamAttitude::Type AAIPawn::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);
	return OtherTeamAgent ? FGenericTeamId::GetAttitude(GetGenericTeamId(), OtherTeamAgent->GetGenericTeamId())
		: ETeamAttitude::Neutral;
}

void AAIPawn::AddPatrolPoint(const TArray<AAIPatrolPoint*>& Array)
{
	int32 Count = Array.Num();

	for (int32 i = 0; i < Count; i++)
	{
		mPatrolArray.Add(Cast<AActor>(Array[i]));
	}
	
}

void AAIPawn::AddPatrolStart(AActor* Actor)
{
	mPatrolArray.Add(Actor);
}

void AAIPawn::RegisterPatrolPoint()
{
	if (mPatrolArray.Num() == 0)
	{
		return;
	}
	
	AAIController* Control = GetController<AAIController>();

	if (IsValid(Control))
	{
		Control->GetBlackboardComponent()->SetValueAsObject(CMonsterDefaultKey::mPatrolPoint, mPatrolArray[mPatrolIndex]);

		bool PatrolEnable = false;
		if (mPatrolArray.Num() > 1)
		{
			PatrolEnable = true;
		}

		Control->GetBlackboardComponent()->SetValueAsBool(CMonsterDefaultKey::mPatrolEnable, PatrolEnable);
	}
}

void AAIPawn::NextPatrolPoint()
{
	mPatrolIndex = (mPatrolIndex + 1) % mPatrolArray.Num();
}

void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AAIPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// Destroy();

	return DamageAmount;
}

void AAIPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (mPatrolArray.Num() == 0)
	{
		return;
	}
	
	AAIController* Control = GetController<AAIController>();

	if (IsValid(Control))
	{
		Control->GetBlackboardComponent()->SetValueAsObject(CMonsterDefaultKey::mPatrolPoint, mPatrolArray[mPatrolIndex]);

		bool PatrolEnable = false;
		if (mPatrolArray.Num() > 1)
		{
			PatrolEnable = true;
		}

		Control->GetBlackboardComponent()->SetValueAsBool(CMonsterDefaultKey::mPatrolEnable, PatrolEnable);
	}
}
