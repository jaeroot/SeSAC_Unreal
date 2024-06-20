// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerCharacter.h"
#include "KnightCharacter.generated.h"

UCLASS()
class SESAC_API AKnightCharacter : public APlayerCharacter
{
	GENERATED_BODY()

public:
	AKnightCharacter();
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	virtual void NormalAttack() override;

	
};
