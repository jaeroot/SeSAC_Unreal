// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionPawn.h"

#include "AIController.h"
#include "BrainComponent.h"
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
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		HitAsset(TEXT("/Game/ParagonKwang/FX/Particles/Abilities/Primary/FX/P_Kwang_Primary_Impact.P_Kwang_Primary_Impact"));
	if (HitAsset.Succeeded())
	{
		mAttackParticle = HitAsset.Object;
	}

	
}

void AMinionPawn::BeginPlay()
{
	Super::BeginPlay();

	mMinionAnim = Cast<UMonsterDefaultAnimTemplate>(mMesh->GetAnimInstance());

	mMinionAnim->SetAnimData(TEXT("Minion"));
}

float AMinionPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	SetAIType(EAIType::Death);
	GetController<AAIController>()->GetBrainComponent()->StopLogic(TEXT("Death"));

	return DamageAmount;
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

void AMinionPawn::Attack()
{
	FVector Start = GetActorLocation() + GetActorForwardVector() * 50.0f;
	FVector End = Start + GetActorForwardVector() * 400.0f;
	FCollisionQueryParams Param;
	Param.AddIgnoredActor(this);
	TArray<FHitResult> Results;
	bool Collision = GetWorld()->SweepMultiByChannel(
		Results,
		Start,
		End,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel8,
		FCollisionShape::MakeSphere(50.0f),
		Param
	);

#if ENABLE_DRAW_DEBUG

	FColor DrawColor = Collision ? FColor::Red : FColor::Green;
	DrawDebugCapsule(
		GetWorld(),
		(Start + End) / 2,
		200.0f,
		50.0f,
		FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor,
		false,
		2.0f
	);
	
#endif
	
	if (Collision)
	{
		// 배열 개수만큼 반복하여 하나씩 Result에 꺼내옴
		for (auto Result: Results)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan,
				FString::Printf(TEXT("Minion Hit : %s"), *Result.ImpactPoint.ToString()));
			
			FDamageEvent DmgEvent;
			Result.GetActor()->TakeDamage(10.0f, DmgEvent, GetController(), this);

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mAttackParticle,
				Result.ImpactPoint, Result.ImpactNormal.Rotation(), true);

			// GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan,
			// 	FString::Printf(TEXT("Weapon Hit : %s"), *Result.GetActor()->GetName()));
		}	
	}
}
