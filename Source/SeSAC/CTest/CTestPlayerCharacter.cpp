// Fill out your copyright notice in the Description page of Project Settings.


#include "CTestPlayerCharacter.h"

ACTestPlayerCharacter::ACTestPlayerCharacter()
{
 	PrimaryActorTick.bCanEverTick = false;

}

void ACTestPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACTestPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACTestPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

