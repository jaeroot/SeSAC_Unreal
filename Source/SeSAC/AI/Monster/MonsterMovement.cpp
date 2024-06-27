// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterMovement.h"


UMonsterMovement::UMonsterMovement()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UMonsterMovement::BeginPlay()
{
	Super::BeginPlay();
	
}


void UMonsterMovement::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

