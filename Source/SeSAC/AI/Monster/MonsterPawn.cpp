// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterPawn.h"

#include "MonsterController.h"
#include "MonsterMovement.h"


AMonsterPawn::AMonsterPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	mMovement = CreateDefaultSubobject<UMonsterMovement>(TEXT("Movement"));
	mMovement->SetUpdatedComponent(RootComponent);

	AIControllerClass = AMonsterController::StaticClass();
}

void AMonsterPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMonsterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}