// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionPawn.h"


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

}

void AMinionPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMinionPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}