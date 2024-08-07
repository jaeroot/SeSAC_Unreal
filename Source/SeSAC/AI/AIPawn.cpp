// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "SeSAC/AI/AIPatrolPoint.h"
#include "SeSAC/UI/Main/CharacterHeadInfoWidget.h"


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

	mMesh->bReceivesDecals = false;


	
	// widget
	mHeadInfoWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HeadInfo"));
	mHeadInfoWidget->SetupAttachment(mMesh);
	static ConstructorHelpers::FClassFinder<UCharacterHeadInfoWidget>
		HeadWidgetClass(TEXT("/Game/UI/Main/WB_CharacterHeadInfo.WB_CharacterHeadInfo_C"));
	if (HeadWidgetClass.Succeeded())
	{
		mHeadInfoWidget->SetWidgetClass(HeadWidgetClass.Class);
	}
	
	mHeadInfoWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	mHeadInfoWidget->SetPivot(FVector2D(0.5, 1.0));
	mHeadInfoWidget->SetDrawSize(FVector2D(200.0, 80.0));
	mHeadInfoWidget->SetWidgetSpace(EWidgetSpace::Screen);
	mHeadInfoWidget->bVisibleInReflectionCaptures = false;
	mHeadInfoWidget->bVisibleInRealTimeSkyCaptures = false;
	mHeadInfoWidget->bReceivesDecals = false;
	mHeadInfoWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAIPawn::BeginPlay()
{
	Super::BeginPlay();

	// MeshComponent가 가지고 있는 Material Element 수 만큼 반복하며 Dynamic Material을 만들어줌
	int32 Count = mMesh->GetNumMaterials();
	for (int32 i = 0; i < Count; i++)
	{
		UMaterialInstanceDynamic* Mtrl = mMesh->CreateDynamicMaterialInstance(i);

		if (IsValid(Mtrl))
		{
			mMaterialDynamicArray.Add(Mtrl);
		}
	}

	

	mHeadInfo = Cast<UCharacterHeadInfoWidget>(mHeadInfoWidget->GetWidget());
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

	if (mDissolveEnable)
	{
		mDissolveAcc += DeltaTime;

		if (mDissolveAcc >= mDissolveTime)
		{
			mDissolveAcc = mDissolveTime;
			mDissolve = -1.5f;

			Destroy();
		}
		else
		{
			mDissolve = UKismetMathLibrary::MapRangeClamped(mDissolveAcc, 0.0, mDissolveTime, 1.5f, -1.5f);
			
			for (auto Mtrl : mMaterialDynamicArray)
			{
				Mtrl->SetScalarParameterValue(TEXT("Dissolve"), mDissolve);
			}
		}
	}
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
