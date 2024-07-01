// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterPawn.h"

#include "MonsterController.h"
#include "MonsterMovement.h"


AMonsterPawn::AMonsterPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	mMovement = CreateDefaultSubobject<UMonsterMovement>(TEXT("Movement"));
	mMovement->SetUpdatedComponent(RootComponent);

	mCapsule->SetCollisionProfileName(TEXT("Monster"));

	AIControllerClass = AMonsterController::StaticClass();
}

void AMonsterPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMonsterPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
}

void AMonsterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AMonsterController* MonsterController = Cast<AMonsterController>(NewController);

	if (IsValid(MonsterController))
	{
		MonsterController->SetTeamID(mTeamID);
	}
}

void AMonsterPawn::SetAIType(EAIType Type)
{
	Super::SetAIType(Type);
}
