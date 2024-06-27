// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UPlayerAnimInstance;
struct FInputActionValue;

UCLASS()
class SESAC_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	void MoveAction(const FInputActionValue& Value);
	void RotationAction(const FInputActionValue& Value);
	void AttackAction();
	void JumpAction();
	void DeathAction();

public:
	virtual void AttackEnable();
	virtual void AttackDisable();
	
protected:
	virtual void NormalAttack();
	

public:

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* mArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* mCamera;

	TObjectPtr<UPlayerAnimInstance> mAnimInstance;
	
	UPROPERTY(VisibleAnywhere)
	UParticleSystem* mNormalAttackHit;
};
