// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "GameFramework/Character.h"
#include "MazeCharacter.generated.h"

struct FInputActionValue;
class URotatingMovementComponent;

UCLASS()
class SESAC_API AMazeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMazeCharacter();
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	void MoveAction(const FInputActionValue& Value);
	void RotationAction(const FInputActionValue& Value);
	void AttackAction();
	void ShieldAction();

private:
	
public:	

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> RotationComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URotatingMovementComponent> RotatingMovementComponent;

	
	TSubclassOf<AActor> ShieldClass;
	
private:
	bool bShieldEnable = true;
	float ShieldTime = 0.0f;
	float ShieldCoolDown = 6.0f;
	
};
