// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "GameFramework/Character.h"
#include "CTestPlayerCharacter.generated.h"

class URotatingMovementComponent;
struct FInputActionValue;

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

	void MoveAction(const FInputActionValue& Value);
	void RotationAction(const FInputActionValue& Value);
	void AttackAction();
	void ShieldAction();

public:

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* mArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* mCamera;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* mRotation;

	UPROPERTY(VisibleAnywhere)
	URotatingMovementComponent* mRotatingMovementComponent;

	// TSubclassOf : UClass 정보를 저장하는 템플릿 객체
	TSubclassOf<AActor> mAttackClass;
	TSubclassOf<AActor> mShieldClass;

private:
	bool bShieldEnable = true;
	float ShieldTime = 0.0f;
};
