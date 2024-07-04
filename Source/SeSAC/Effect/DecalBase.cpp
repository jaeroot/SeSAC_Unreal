// Fill out your copyright notice in the Description page of Project Settings.


#include "DecalBase.h"

ADecalBase::ADecalBase()
{
 	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(mRoot);

	mDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	mDecal->SetRelativeRotation((FRotator(-90.0f, 0.0f, 0.0f)));
	mDecal->DecalSize = FVector(128.0f, 256.0f, 256.0f);
	mDecal->SetupAttachment(mRoot);

	mRoot->bVisualizeComponent = true;
}

void ADecalBase::BeginPlay()
{
	Super::BeginPlay();

	// Dynamic Material 생성
	mDynamicMaterial = mDecal->CreateDynamicMaterialInstance();
}

void ADecalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mOpacity -= DeltaTime / 10.0f;
	if (mDynamicMaterial)
	{
		mDynamicMaterial->SetScalarParameterValue(TEXT("Opacity"), mOpacity);
	}

	mGlow += DeltaTime * 5.0f;
	if (mDynamicMaterial)
	{
		mDynamicMaterial->SetScalarParameterValue(TEXT("Glow"), mGlow);
	}
}

void ADecalBase::SetOriginMaterial(UMaterialInterface* Material)
{
	mDecal->SetDecalMaterial(Material);

	// Dynamic Material 생성
	mDynamicMaterial = mDecal->CreateDynamicMaterialInstance();
}
