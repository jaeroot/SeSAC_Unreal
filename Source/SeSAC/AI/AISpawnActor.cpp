// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawnActor.h"

#include "AIPawn.h"


AAISpawnActor::AAISpawnActor()
{
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(mRoot);

#if WITH_EDITORONLY_DATA
	mRoot->bVisualizeComponent = true;

	mArrow = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	mArrow->ArrowColor = FColor(150, 200, 255);
	mArrow->bTreatAsASprite = true;
	mArrow->SetupAttachment(mRoot);
	mArrow->bIsScreenSizeScaled = true;
	mArrow->SetSimulatePhysics(false);
#endif
	
}

void AAISpawnActor::BeginPlay()
{
	Super::BeginPlay();

	Spawn();
}

void AAISpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!mSpawnActor)
	{
		mCalculateSpawnTime += DeltaTime;

		if (mSpawnTime <= mCalculateSpawnTime)
		{
			mCalculateSpawnTime = 0.0f;
			Spawn();
		}
	}
}

void AAISpawnActor::Spawn()
{
	if (!IsValid(mSpawnClass))
	{
		return;
	}

	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotator = GetActorRotation();

	// UClass는 Class Default Object를 가지고 있음
	AAIPawn* DefaultPawn = mSpawnClass->GetDefaultObject<AAIPawn>();
	if (IsValid(DefaultPawn))
	{
		SpawnLocation.Z += DefaultPawn->GetCapsule()->GetScaledCapsuleHalfHeight();
	}
	
	mSpawnActor = GetWorld()->SpawnActor<AAIPawn>(mSpawnClass, SpawnLocation, SpawnRotator);

	mSpawnActor->AddPatrolStart(this);
	mSpawnActor->AddPatrolPoint(mPatrolArray);

	mSpawnActor->RegisterPatrolPoint();

	mSpawnActor->AddDeathDelegate<ThisClass>(this, &AAISpawnActor::AIDeathDelegate);
}

void AAISpawnActor::AIDeathDelegate()
{
	mSpawnActor = nullptr;
}

