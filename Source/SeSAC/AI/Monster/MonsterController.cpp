// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterController.h"

#include "Perception/AIPerceptionComponent.h"


AMonsterController::AMonsterController()
{
	PrimaryActorTick.bCanEverTick = true;

	mAIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
}

void AMonsterController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMonsterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

