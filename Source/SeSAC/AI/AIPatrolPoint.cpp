// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPatrolPoint.h"

AAIPatrolPoint::AAIPatrolPoint()
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

void AAIPatrolPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAIPatrolPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

