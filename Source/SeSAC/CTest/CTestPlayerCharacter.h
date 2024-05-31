// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CTestPlayerCharacter.generated.h"

UCLASS()
class SESAC_API ACTestPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACTestPlayerCharacter();
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

public:	

};
