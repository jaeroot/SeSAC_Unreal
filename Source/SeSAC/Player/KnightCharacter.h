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

public:
	virtual void AttackEnable();
	virtual void AttackDisable();

protected:
	virtual void NormalAttack() override;
	
	UFUNCTION()
	void WeaponHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void WeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* mWeaponBox;
};
