// Fill out your copyright notice in the Description page of Project Settings.


#include "CircularSectorDecal.h"

#include "Components/DecalComponent.h"
#include "Kismet/KismetMathLibrary.h"

ACircularSectorDecal::ACircularSectorDecal()
{
	PrimaryActorTick.bCanEverTick = true;
	
	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(mRoot);

	mDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	mDecal->SetRelativeRotation((FRotator(-90.0f, 0.0f, 0.0f)));
	mDecal->SetRelativeScale3D(FVector(1.0f, 3.0,3.0f));
	mDecal->DecalSize = FVector(128.0f, 256.0f, 256.0f);
	mDecal->SetupAttachment(mRoot);

	mRoot->bVisualizeComponent = true;
}

void ACircularSectorDecal::BeginPlay()
{
	Super::BeginPlay();
	
	mDynamicMaterial = mDecal->CreateDynamicMaterialInstance();

	mDynamicMaterial->SetScalarParameterValue(TEXT("SectorCount"), SectorCount);
}

void ACircularSectorDecal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (RangeTimeAcc < RangeTime)
	{
		RangeTimeAcc += DeltaTime;

		if (RangeTimeAcc >= RangeTime)
		{
			RangeTimeAcc = RangeTime;
		}
		
		Radius = UKismetMathLibrary::MapRangeClamped(RangeTimeAcc, 0.0f, RangeTime, 0.0f, 0.5f);
		mDynamicMaterial->SetScalarParameterValue(TEXT("Radius"), Radius);
	}
}

