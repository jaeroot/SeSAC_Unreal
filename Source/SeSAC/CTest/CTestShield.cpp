// Fill out your copyright notice in the Description page of Project Settings.

#include "CTestShield.h"

ACTestShield::ACTestShield()
{
	PrimaryActorTick.bCanEverTick = true;

	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(mMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshAsset(TEXT("/Game/Test/TestMesh/Cube.Cube"));
	if (MeshAsset.Succeeded())
	{
		mMesh->SetStaticMesh(MeshAsset.Object);
	}
	mMesh->SetRelativeScale3D(FVector(0.1f, 0.25f, 0.25f));

	SetLifeSpan(5.0f);
}

void ACTestShield::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACTestShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

