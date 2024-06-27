// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"


AAIPawn::AAIPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(mCapsule);
	
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mMesh->SetupAttachment(mCapsule);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}